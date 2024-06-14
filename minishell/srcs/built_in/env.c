/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:44:24 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/14 16:19:34 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	put_line_return(void)
{
	printf("\n");
	return (SUCCESS);
}

int	exec_env(t_env *head)
{
	t_env	*current;
	int			i;

	current = head;;
	printf("env\n");
	if (!current)
		return (put_line_return());
	printf("env_1\n");
	while (current)
	{
		printf("%s=", current->key);
		i = 0;
		while (i < current->num_value)
		{
			printf("%s", current->value[i]);
			if (i < current->num_value - 1)
			{
				printf(":");
			}
			i++;
		}
		printf("\n");
		current = current->next;
	}
	return (SUCCESS);
}
