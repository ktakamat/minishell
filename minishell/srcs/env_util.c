/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:06:19 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/16 18:19:44 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*new_env_node(char *env_str)
{
	t_env	*node;
	char	*separator;
	int		name_len;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	separator = ft_strchr(env_str, '=');
	if (!separator)
	{
		free(node);
		return (NULL);
	}
	name_len = separator - env_str;
	node->env_name = malloc(name_len + 1);
	ft_strncpy(node->env_name, env_str, name_len);
	node->env_name[name_len] = '\0';
	node->env_val = strdup(separator + 1);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_env	*set_env_list(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;

	head = NULL;
	tail = NULL;
	while (*envp)
	{
		new_node = new_env_node(*envp);
		if (!new_node)
		{
			perror("Failed to create env node");
			continue ;
		}
		if (tail)
		{
			tail->next = new_node;
			new_node->prev = tail;
		}
		else
			head = new_node;
		tail = new_node;
		envp++;
	}
	return (head);
}

void	print_env_list(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		printf("Env Name: %s, Env Value: %s\n", current->env_name,
			current->env_val);
		current = current->next;
	}
}
