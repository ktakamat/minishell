/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_heredoc_help.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:27:48 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/25 19:27:14 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	simple_insert(char *new, char c, int *count, int *i)
{
	new[*count] = c;
	(*count)++;
	(*i)++;
}

void	str_insert(char	*new, char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		new[len] = str[len];
		len++;
	}
	return ;
}

int	question_add(char *new, int *i, int *count)
{
	int		len;
	char	*tmp;

	tmp = ft_itoa_2(g_interrupted);
	len = ft_strlen(tmp);
	*i += 2;
	str_insert(new, tmp);
	free(tmp);
	*count = *count + len;
	return (len);
}
