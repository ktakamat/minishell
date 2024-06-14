/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:43:51 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/14 16:49:54 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_split_first(const char *s, char c)
{
	char	**arr;
	char	*location;

	arr = malloc(2 * sizeof(char *));
	if (!arr)
		return (NULL);
	location = ft_strchr(s, c);
	if (location)
	{
		arr[0] = ft_strndup(s, location - s);
		if (!arr[0])
			return (NULL);
		arr[1] = ft_strdup(location + 1);
		if (!arr[1])
			return (null_free(arr[0]));
	}
	else
	{
		arr[0] = ft_strdup(s);
		if (!arr[0])
			return (NULL);
		arr[1] = NULL;
	}
	return (arr);
}

static t_env	*check_node(t_env **head, char *key)
{
	t_env	*current;

	current = *head;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

static t_env	*create_env_var(char *key, char *values)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		exit(EXIT_FAILURE);
	new_var->key = key;
	new_var->value = ft_split(values, ':');
	new_var->num_value = count_values(new_var->value);
	ft_free(values);
	new_var->is_shell_var = false;
	new_var->next = NULL;
	return (new_var);
}

static int	add_env_var(t_env **head, char *env_str)
{
	char		*key;
	char		*value;
	char		**split_result;
	t_env		*new_var;
	t_env		*existing_node;

	split_result = ft_split_first(env_str, '=');
	if (!split_result)
		exit(EXIT_FAILURE);
	key = split_result[0];
	value = split_result[1];
	existing_node = check_node(head, key);
	if (existing_node)
		return (exist_value(existing_node, value, split_result, key));
	new_var = create_env_var(key, value);
	new_var->next = *head;
	*head = new_var;
	free(split_result);
	return (SUCCESS);
}

int	exe_export(t_env **head, char **cmds, int *flags)
{
	int		status;
	int		i;
	char	*s1;

	status = SUCCESS;
	i = 0;
	while (cmds[++i])
	{
		s1 = check_equal(cmds[i]);
		if (!s1)
		{
			if (flags[i] == 0 && is_valid_name(cmds[i]))
				status = FAILURE;
		}
		else
		{
			if (s1[0] == '=')
				status = FAILURE;
			else if (flags[i] == 0 && is_valid_name(s1))
				status = FAILURE;
			else if (add_env_var(head, s1))
				return (EXIT_ERROR);
		}
	}
	return (status);
}
