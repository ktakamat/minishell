/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:18:10 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/14 16:03:42 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parser_error(t_parser *parser_head, char *current_str);

bool	lexer_connect_check(t_token *lexer)
{
	if (lexer->kind == TK_PIPE)
		return (put_error(PARSE_ERROR_REDIRECT_STR, "|"), false);
	if (is_pipe_redirect(lexer))
	{
		if (lexer->next == NULL)
			return (put_error(PARSE_ERROR_REDIRECT, ""), false);
		else if (lexer->next != NULL && lexer->next->kind == TK_PIPE)
			return (put_error(PARSE_ERROR_REDIRECT_STR, "|"), false);
		else if (is_redirect(lexer) && is_redirect(lexer->next))
			return (put_error(PARSE_ERROR_REDIRECT_STR, lexer->next->str) \
					, false);
	}
	return (true);
}

t_parser	*parser(t_token	*lexer, t_env **env)
{
	t_token		*lexer_tmp;
	t_parser	*parser;
	t_parser	*parser_tmp;

	if (lexer == NULL || !lexer_connect_check(lexer))
		return (NULL);
	if (!token_check_pipe_redirect(lexer) \
		|| expand(lexer, env) == false || token_check_str(lexer) == false)
		return (NULL);
	lexer_tmp = lexer;
	parser = parser_node_new();
	if (parser == NULL)
		return (NULL);
	parser_tmp = parser;
	while (lexer_tmp != NULL)
	{
		while (lexer_tmp != NULL && !lexer_null_check(lexer_tmp))
			lexer_tmp = lexer_tmp->next;
		if (lexer_tmp == NULL)
			break ;
		if (parser_check(&lexer_tmp, &parser_tmp, &parser) == NULL)
			return (parser_error(parser, lexer_tmp->str), NULL);
		lexer_tmp = lexer_tmp->next;
	}
	return (parser);
}

void	*parser_check(t_token **lexer_tmp, t_parser **parser_tmp, \
											t_parser **parser)
{
	if ((*lexer_tmp)->kind == TK_PIPE)
	{
		if (!((*lexer_tmp)->next) || parser_pipe(parser_tmp, parser) == NULL)
			return (NULL);
	}
	else if (is_redirect((*lexer_tmp)) == true)
	{
		if (!((*lexer_tmp)->next)
			|| parser_redirect(lexer_tmp, parser_tmp) == NULL)
			return (NULL);
	}
	else
	{
		if (parser_cmd(lexer_tmp, parser_tmp) == NULL)
			return (NULL);
	}
	return (parser_tmp);
}

t_parser	*parser_node_new(void)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->cmd = NULL;
	new->file = NULL;
	return (new);
}

static void	parser_error(t_parser *parser_head, char *current_str)
{
	char	current;

	free_parser(parser_head);
	if (current_str == NULL)
		current = '\0';
	else
		current = *current_str;
	put_error(PARSE_ERROR, &current);
}
