/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ver.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:24:17 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/11 16:09:37 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*check_split(t_env *head)
{
	t_env	*current;
	t_env	*next;
	int			i;

	current = head;
	while (current)
	{
		next = current->next;
		ft_free(current->key);
		i = 0;
		while (i < current->num_value)
		{
			ft_free(current->value[i]);
			i++;
		}
		ft_free(current->value);
		ft_free(current);
		current = next;
	}
	return (NULL);
}

static t_env	*i_new_var(char *key, char *value, bool is_shell_var)
{
	t_env	*new_var;
	char		**p;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	new_var->value = ft_split(value, ':');
	if (!new_var->value)
		exit(EXIT_FAILURE);
	new_var->num_value = 0;
	p = new_var->value;
	while (*p)
	{
		new_var->num_value++;
		p++;
	}
	new_var->key = key;
	ft_free(value);
	new_var->is_shell_var = is_shell_var;
	new_var->next = NULL;
	return (new_var);
}

static void	helper_env(char **split_result, t_env **head, t_env **prev)
{
	char		*key;
	char		*value;
	t_env	*new_var;

	key = split_result[0];
	value = split_result[1];
	new_var = i_new_var(key, value, false);
	if (*prev == NULL)
		*head = new_var;
	else
		(*prev)->next = new_var;
	*prev = new_var;
	ft_free(split_result);
}

t_env	*create_env_vars(char *envp[], char *path)
{
	t_env	*head;
	t_env	*prev;
	int			i;
	char		**split_result;

	i = 0;
	head = NULL;
	prev = NULL;
	if (envp[i] == NULL)
	{
		set_ready_env_vars(&head, path);
		return (head);
	}
	while (envp[i] != NULL)
	{
		split_result = ft_split(envp[i], '=');
		if (!split_result)
			return (check_split(head));
		helper_env(split_result, &head, &prev);
		i++;
	}
	return (head);
}
