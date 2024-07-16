/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:17:01 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/11 13:15:03 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	start_check(t_token *tmp)
{
	if (tmp->kind == TK_CMD || tmp->kind == TK_SQUOTE || tmp->kind == TK_DQUOTE)
		return (true);
	return (false);
}

bool	connect_check(t_token *tmp)
{
	if (tmp->kind == TK_CMD || tmp->kind == TK_SQUOTE || tmp->kind == TK_DQUOTE)
		return (true);
	return (false);
}

void	node_delete(t_token *tmp, t_token *tmp_next)
{
	t_token	*tmp2;

	tmp2 = tmp_next->next;
	tmp->space_flag = tmp_next->space_flag;
	tmp->next = tmp2;
	free(tmp_next->str);
	free(tmp_next);
}

bool	token_check_str(t_token	*lexer)
{
	t_token	*tmp;
	char	*new;

	tmp = lexer;
	while (tmp->next != NULL && tmp != NULL)
	{
		if (tmp->space_flag == false)
		{
			if (start_check(tmp) && connect_check(tmp->next))
			{
				new = ft_strjoin(tmp->str, tmp->next->str);
				if (new == NULL)
					return (false);
				free(tmp->str);
				tmp->str = new;
				node_delete(tmp, tmp->next);
			}
			else
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return (true);
}
