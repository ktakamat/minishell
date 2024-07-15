/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:44:24 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/02 21:02:38 by ktakamat         ###   ########.fr       */
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
	int		i;

	current = head;
	if (!current)
		return (put_line_return());
	while (current)
	{
		if (ft_strncmp(current->key, "OLDPWD", 6) != 0)
			printf("%s=", current->key);
		i = 0;
		while (i < current->num_value)
		{
			if (ft_strncmp(current->key, "OLDPWD", 6) != 0)
				printf("%s", current->value[i]);
			if (i < current->num_value - 1)
				printf(":");
			i++;
		}
		if (ft_strncmp(current->key, "C_INCLUDE_PATH", 6) == 0
			|| ft_strncmp(current->key, "LIBRARY_PATH", 6) == 0)
			printf(":");
		printf("\n");
		current = current->next;
	}
	return (SUCCESS);
}
