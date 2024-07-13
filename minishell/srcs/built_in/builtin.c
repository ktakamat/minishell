/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:51:39 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/13 08:17:10 by flaghata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_cmds(char **cmds, t_directory *dir,
			t_env **env_var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds[i])
	{
		printf("coms :%d %s\n",i,cmds[i]);
		cmds[i] = expansion(cmds[i], dir, env_var);
		if (cmds[i] && cmds[i][0] != '\0')
		{
			cmds[j++] = cmds[i];
		}
		else if (cmds[i][0] == '\0')
			ft_free(cmds[i]);
		i++;
	}
	cmds[j] = NULL;
}

static int	*set_flags(char **cmds)
{
	int	i;
	int	*flags;
	int	k;

	i = 0;
	while (cmds[i])
		i++;
	flags = ft_calloc(i, sizeof(int));
	if (!flags)
		exit(EXIT_FAILURE);
	k = 0;
	while (cmds[k])
	{
		if (is_quoted(cmds[k]))
			flags[k] = 1;
		k++;
	}
	return (flags);
}

static int	exec_export(char **cmds, t_env **env_var, int *falgs)
{
	int		status;

	status = SUCCESS;
	if (!cmds[1])
		return (ft_declare(*env_var));
	status = exe_export(env_var, cmds, falgs);
	if (status == EXIT_ERROR)
		exit(EXIT_FAILURE);
	return (status);
}

static void	execute_com(char **cmds, t_directory *dir,
			t_env **env_vars, int *flags)
{
	int	i;

	if (!ft_strcmp(cmds[0], "pwd"))
		dir->error.error_num = exec_pwd(dir);
	else if (!ft_strcmp(cmds[0], "cd"))
		dir->error.error_num = exec_cd(dir, cmds[1], env_vars);
	else if (!ft_strcmp(cmds[0], "exit"))
		dir->error.error_num = exec_exit(cmds + 1);
	else if (!ft_strcmp(cmds[0], "env"))
		dir->error.error_num = exec_env(*env_vars);
	else if (!ft_strcmp(cmds[0], "echo"))
	{
		i = 0;
		while (cmds[i])
			i++;
		dir->error.error_num = exec_echo(cmds, i - 1);
	}
	else if (!ft_strcmp(cmds[0], "export"))
		dir->error.error_num = exec_export(cmds, env_vars, flags);
	else if (!ft_strcmp(cmds[0], "unset"))
		dir->error.error_num = exec_unset(env_vars, cmds, flags);
}

void	exec_builtin(char **cmds, t_directory *dir, t_env **env_vars)
{
	int	*flags;

	flags = set_flags(cmds);
	if (validate_cmds(cmds, dir, env_vars))
		return ;
	execute_com(cmds, dir, env_vars, flags);
	ft_free(flags);
}
