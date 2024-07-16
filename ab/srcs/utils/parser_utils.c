/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:04:19 by yususato          #+#    #+#             */
/*   Updated: 2024/07/14 15:33:25 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	lexer_null_check(t_token *lexer)
{
	if (lexer->str[0] == '\0' && lexer->kind == TK_CMD)
		return (false);
	return (true);
}

int	is_special_space(char *str)
{
	int	len;

	len = 0;
	while (str[len] && ft_isalnum(str[len]))
		len++;
	return (len);
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

void	simple_counter(int *i, int *count)
{
	(*i)++;
	(*count)++;
}

void	simple_insert(char *new, char c, int *count, int *i)
{
	new[*count] = c;
	(*count)++;
	(*i)++;
}
