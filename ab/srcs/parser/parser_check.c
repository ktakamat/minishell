/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:12:03 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/11 13:15:11 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(t_token *lexer_tmp)
{
	if (lexer_tmp->kind == TK_LESS || lexer_tmp->kind == TK_DLESS \
		|| lexer_tmp->kind == TK_GREAT || lexer_tmp->kind == TK_DGREAT)
		return (true);
	else
		return (false);
}

bool	is_pipe_redirect(t_token *lexer_tmp)
{
	if (lexer_tmp->kind == TK_LESS || lexer_tmp->kind == TK_DLESS \
		|| lexer_tmp->kind == TK_GREAT || lexer_tmp->kind == TK_DGREAT \
		|| lexer_tmp->kind == TK_PIPE)
		return (true);
	else
		return (false);
}

bool	is_lexer_continue(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	else
		return (false);
}

bool	is_quote(t_token_kind kind)
{
	if (kind == TK_SQUOTE || kind == TK_DQUOTE)
		return (true);
	else
		return (false);
}
