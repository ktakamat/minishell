/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:59:27 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/16 20:08:03 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exist_value(t_env *exist_node,
	char *values, char **split_result, char *key)
{
	int	i;

	i = 0;
	while (i < exist_node->num_value)
	{
		ft_free(exist_node->value[i]);
		i++;
	}
	ft_free(exist_node->value);
	exist_node->value = ft_split(values, ':');
	if (!exist_node->value)
		exit(EXIT_FAILURE);
	exist_node->num_value = count_values(exist_node->value);
	ft_free(values);
	ft_free(split_result);
	ft_free(key);
	return (SUCCESS);
}

char	**null_free(char *str)
{
	ft_free(str);
	return (NULL);
}
