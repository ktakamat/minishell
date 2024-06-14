/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:15:34 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/14 16:26:00 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_env_var(t_env **head, char *key,
			char *value, bool is_shell_var)
{
	t_env	*new_var;

	new_var = (t_env *)malloc(sizeof(t_env));
	if (!new_var)
		exit(EXIT_FAILURE);
	new_var->key = ft_strdup(key);
	new_var->value = (char **)malloc(2 * sizeof(char *));
	if (!new_var->key || !new_var->value)
		exit(EXIT_FAILURE);
	new_var->value[0] = ft_strdup(value);
	if (!new_var->value[0])
		exit(EXIT_FAILURE);
	new_var->value[1] = NULL;
	new_var->num_value = 1;
	new_var->is_shell_var = is_shell_var;
	new_var->next = *head;
	*head = new_var;
}

void	set_ready_env_vars(t_env **head, char *path)
{
	add_env_var(head, "PWD", path, false);
	add_env_var(head, "SHLVL", "1", false);
	add_env_var(head, "_", "/usr/bin/env", false);
}
