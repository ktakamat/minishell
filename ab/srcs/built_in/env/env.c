/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:55:42 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/15 17:34:57 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_env(t_env *env, bool is_export)
{
	t_env	*current;
	char	*value;

	g_flag = 0;
	if (env == NULL)
		return ;
	current = env;
	while (current != NULL)
	{
		if (current->value == NULL)
			value = "\0";
		else
			value = current->value;
		if (is_export)
			printf("declare -x %s=\"%s\"\n", current->key, value);
		else
			printf("%s=%s\n", current->key, value);
		current = current->next;
	}
}
