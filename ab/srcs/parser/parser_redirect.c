/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:12:51 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/11 13:15:05 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	file_init(t_file **file, char *file_name, t_token_kind kind, \
												t_token_kind next_kind)
{
	(*file) = (t_file *)malloc(sizeof(t_file));
	if ((*file) == NULL)
		return (false);
	(*file)->next = NULL;
	(*file)->file_name = ft_strdup(file_name);
	if ((*file)->file_name == NULL)
		return (false);
	if (kind == TK_DLESS && is_quote(next_kind) == true)
		(*file)->type = QUOTE_HEREDOC;
	else if (kind == TK_DLESS)
		(*file)->type = HEREDOC;
	else if (kind == TK_LESS)
		(*file)->type = IN_FILE;
	else if (kind == TK_DGREAT)
		(*file)->type = APPEND;
	else if (kind == TK_GREAT)
		(*file)->type = OUT_FILE;
	return (true);
}

bool	file_add(t_file **file, char *file_name, t_token_kind kind, \
												t_token_kind next_kind)
{
	t_file	*tmp;

	tmp = *file;
	while ((tmp)->next != NULL)
		(tmp) = (tmp)->next;
	(tmp)->next = (t_file *)malloc(sizeof(t_file));
	if ((tmp)->next == NULL)
		return (false);
	(tmp) = (tmp)->next;
	(tmp)->next = NULL;
	(tmp)->file_name = ft_strdup(file_name);
	if ((tmp)->file_name == NULL)
		return (false);
	if (kind == TK_DLESS && is_quote(next_kind) == true)
		(tmp)->type = QUOTE_HEREDOC;
	else if (kind == TK_DLESS)
		(tmp)->type = HEREDOC;
	else if (kind == TK_LESS)
		(tmp)->type = IN_FILE;
	else if (kind == TK_DGREAT)
		(tmp)->type = APPEND;
	else if (kind == TK_GREAT)
		(tmp)->type = OUT_FILE;
	return (true);
}

bool	parser_output(t_token **lexer_tmp, t_parser **parser_tmp)
{
	if ((*lexer_tmp)->next == NULL)
		return (false);
	if ((*parser_tmp)->file == NULL)
		return (file_init(&(*parser_tmp)->file, (*lexer_tmp)->next->str, \
					(*lexer_tmp)->kind, (*lexer_tmp)->next->kind));
	else
		return (file_add(&(*parser_tmp)->file, (*lexer_tmp)->next->str, \
					(*lexer_tmp)->kind, (*lexer_tmp)->next->kind));
}

bool	parser_input(t_token **lexer_tmp, t_parser **parser_tmp)
{
	if ((*lexer_tmp)->next == NULL)
		return (false);
	if ((*parser_tmp)->file == NULL)
		return (file_init(&(*parser_tmp)->file, (*lexer_tmp)->next->str, \
					(*lexer_tmp)->kind, (*lexer_tmp)->next->kind));
	else
		return (file_add(&(*parser_tmp)->file, (*lexer_tmp)->next->str, \
					(*lexer_tmp)->kind, (*lexer_tmp)->next->kind));
}

void	*parser_redirect(t_token **lexer_tmp, t_parser **parser_tmp)
{
	while (is_redirect(*lexer_tmp))
	{
		if ((*lexer_tmp)->next == NULL)
			break ;
		if ((*lexer_tmp)->kind == TK_LESS || (*lexer_tmp)->kind == TK_DLESS)
		{
			if (parser_output(lexer_tmp, parser_tmp) == false)
				return (NULL);
		}
		else if ((*lexer_tmp)->kind == TK_GREAT
			|| (*lexer_tmp)->kind == TK_DGREAT)
		{
			if (parser_input(lexer_tmp, parser_tmp) == false)
				return (NULL);
		}
		else
			*lexer_tmp = (*lexer_tmp)->next;
		*lexer_tmp = (*lexer_tmp)->next;
	}
	return (parser_tmp);
}
