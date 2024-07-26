/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:44:24 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/25 17:42:52 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	put_line_return(void)
{
	printf("\n");
	return (SUCCESS);
}

void	print_env_value(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_value)
	{
		printf("%s", env->value[i]);
		if (i < env->num_value - 1)
			printf(":");
		i++;
	}
}

void	print_env_line(t_env *env)
{
	if (strncmp(env->key, "OLDPWD", 6) != 0)
		printf("%s=", env->key);
	print_env_value(env);
	if (strncmp(env->key, "C_INCLUDE_PATH", 6) == 0
		|| strncmp(env->key, "LIBRARY_PATH", 6) == 0)
		printf(":");
	printf("\n");
}

int	exec_env(t_env *head)
{
	t_env	*current;

	current = head;
	if (!current)
		return (put_line_return());
	while (current)
	{
		print_env_line(current);
		current = current->next;
	}
	return (SUCCESS);
}
