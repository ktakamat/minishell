/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:50:19 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/05 17:32:32 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*_getenv(t_env *env_head, char *key)
{
	t_env	*env_node;
	char	*env_line;

	if (env_head == NULL || key == NULL)
		return (NULL);
	env_node = find_node(env_head, key);
	if (env_node == NULL || env_node->value == NULL)
		return (NULL);
	env_line = ft_strdup(env_node->value);
	if (env_line == NULL)
		return (NULL);
	return (env_line);
}

t_env	*find_node(t_env *env_head, char *key)
{
	t_env	*current;

	if (env_head == NULL || key == NULL)
		return (NULL);
	current = env_head;
	while (is_equal(current->key, key) != 1 && current->next != NULL)
		current = current->next;
	if (is_equal(current->key, key) == 1)
		return (current);
	else
		return (NULL);
}

void	push_env(t_env *env_head, t_env *new_node)
{
	t_env	*current;
	t_env	*current_next;

	if (env_head == NULL || new_node == NULL)
		return ;
	current = env_head;
	if (current == NULL)
		return ;
	while (current->next != NULL)
		current = current->next;
	current_next = current->next;
	current->next = new_node;
	new_node->next = current_next;
}

int	remove_env(t_env *previous)
{
	t_env	*for_free;

	if (previous == NULL || previous->next == NULL)
		return (-1);
	for_free = previous->next;
	previous->next = for_free->next;
	free_node(for_free);
	return (0);
}
