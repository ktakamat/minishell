/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:44:33 by h.miyazaki        #+#    #+#             */
/*   Updated: 2024/07/15 17:03:26 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_destination(char **cmd, t_env *env);
static int	change_dir_env(t_env *env, char *new_cwd);
static void	change_old_pwd(t_env *env);

void	_cd(char **cmd, t_env *env)
{
	char	*destination;

	destination = set_destination(cmd, env);
	if (destination == NULL || *destination == '\0')
		return ;
	if (chdir(destination) != 0)
	{
		write(2, "minishell: cd: ", 15);
		perror_set_flag(destination);
		return (free(destination));
	}
	change_dir_env(env, destination);
	g_flag = 0;
	free(destination);
}

static char	*set_destination(char **cmd, t_env *env)
{
	char	*home;

	if (cmd == NULL || cmd[0] == NULL)
		return (NULL);
	if (cmd[1] != NULL)
		return (ft_strdup(cmd[1]));
	home = _getenv(env, "HOME");
	if (home == NULL)
		write(2, "minishell: cd: HOME not set\n", 28);
	return (home);
}

static int	change_dir_env(t_env *env, char *new_cwd)
{
	t_env	*pwd_node;
	char	*allocated_cwd;

	if (env == NULL || new_cwd == NULL)
		return (-1);
	change_old_pwd(env);
	pwd_node = find_node(env, "PWD");
	if (pwd_node == NULL)
	{
		export_action(&env, "PWD=", EQUAL);
		pwd_node = find_node(env, "PWD");
	}
	if (pwd_node == NULL)
		return (-1);
	allocated_cwd = getcwd(NULL, 0);
	if (allocated_cwd != NULL)
	{
		if (pwd_node->value != NULL)
			free(pwd_node->value);
		pwd_node->value = allocated_cwd;
	}
	return (0);
}

static void	change_old_pwd(t_env *env)
{
	t_env	*oldpwd_node;
	t_env	*pwd_node;

	oldpwd_node = find_node(env, "OLDPWD");
	pwd_node = find_node(env, "PWD");
	if (oldpwd_node == NULL)
	{
		export_action(&env, "OLDPWD=", EQUAL);
		oldpwd_node = find_node(env, "OLDPWD");
	}
	if (oldpwd_node->value != NULL)
		free(oldpwd_node->value);
	if (pwd_node == NULL)
		oldpwd_node->value = NULL;
	else
	{
		oldpwd_node->value = pwd_node->value;
		pwd_node->value = NULL;
	}
}
