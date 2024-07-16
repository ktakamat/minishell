/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:07:07 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/11 09:30:51 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_export	check_envvars(char *envvars);

void	_export(char **cmd, t_env **env_head)
{
	t_export	type;
	int			envvar_index;

	g_flag = 0;
	envvar_index = 1;
	if (cmd == NULL || env_head == NULL)
		return ;
	if (cmd[1] == NULL)
		return (_env(*env_head, true));
	while (cmd[envvar_index] != NULL)
	{
		type = check_envvars(cmd[envvar_index]);
		if (type == INVALID)
		{
			put_error(EXPORT_ERROR, cmd[envvar_index]);
			envvar_index++;
			continue ;
		}
		export_action(env_head, cmd[envvar_index], type);
		envvar_index++;
	}
}

bool	is_valid_envkey(char *envvars)
{
	int	index;

	index = 0;
	if (envvars == NULL || ('0' <= envvars[0] && envvars[0] <= '9'))
		return (false);
	if (envvars[0] == '\0' || envvars[0] == '=' || envvars[0] == '+')
		return (false);
	while (envvars[index] != '\0' \
		&& envvars[index] != '=' && envvars[index] != '+')
	{
		if (ft_isalnum(envvars[index]) == 0 && envvars[index] != '_')
			return (false);
		index += 1;
	}
	return (true);
}

int	rewrite_value(char **before, char *after, t_export type)
{
	char	*tmp;

	if (before == NULL || after == NULL)
		return (-1);
	if (type == ADDITION)
	{
		tmp = *before;
		*before = ft_strjoin(*before, after);
		free(tmp);
		if (before == NULL)
			return (-1);
	}
	else
	{
		free(*before);
		*before = ft_strdup(after);
		if (before == NULL)
			return (-1);
	}
	return (0);
}

static t_export	check_envvars(char *envvars)
{
	int	index;

	index = 0;
	if (is_valid_envkey(envvars) == false)
		return (INVALID);
	while (envvars[index] != '\0' \
		&& envvars[index] != '=' && envvars[index] != '+')
		index += 1;
	if (envvars[index] == '+')
	{
		if (envvars[index + 1] == '=')
			return (ADDITION);
		else
			return (INVALID);
	}
	return (EQUAL);
}

void	export_action(t_env **env_head, char *envvars, t_export type)
{
	t_env	*target;
	t_env	*new_node;

	if (env_head == NULL || envvars == NULL)
		return ;
	new_node = create_envnode(envvars);
	if (new_node == NULL)
		return ;
	if (*env_head == NULL)
	{
		*env_head = new_node;
		return ;
	}
	target = find_node(*env_head, new_node->key);
	if (target == NULL)
		push_env(*env_head, new_node);
	else
	{
		rewrite_value(&target->value, new_node->value, type);
		free_node(new_node);
	}
}
