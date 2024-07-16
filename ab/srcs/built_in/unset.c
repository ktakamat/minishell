/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:07:32 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/11 13:15:28 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_head(t_env **env_head);
static void	find_and_unset(t_env *env_head, char *envkey);

void	_unset(char **cmd, t_env **env)
{
	t_env	*current;
	int		index;

	g_flag = 0;
	index = 1;
	if (env == NULL || *env == NULL || cmd == NULL || cmd[0] == NULL)
		return ;
	while (cmd[index] != NULL)
	{
		g_flag = 0;
		current = *env;
		if (is_valid_envkey(cmd[index]) == false)
			put_error(UNSET_ERROR, cmd[index]);
		else if (is_equal((*env)->key, cmd[index]) == 1)
			remove_env_head(env);
		else
			find_and_unset(*env, cmd[index]);
		index += 1;
	}
}

static void	remove_env_head(t_env **env_head)
{
	t_env	*for_free;

	for_free = *env_head;
	*env_head = (*env_head)->next;
	free_node(for_free);
}

static void	find_and_unset(t_env *env_head, char *envkey)
{
	t_env	*current;

	current = env_head;
	while (current->next != NULL && is_equal(current->next->key, envkey) == 0)
		current = current->next;
	if (current->next != NULL && is_equal(current->next->key, envkey) == 1)
		remove_env(current);
}
