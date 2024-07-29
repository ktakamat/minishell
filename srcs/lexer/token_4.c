/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:23:09 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/29 17:32:28 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser	*exit_parser_pipe(int *error, t_directory *dir, t_token *tmp)
{
	*error = 258;
	syntax_error_pipe();
	syntax_error_code(dir, error);
	token_clear(tmp);
	return (NULL);
}

t_parser	*exit_parser_token(int *error, t_directory *dir, t_token *tmp)
{
	*error = 258;
	syntax_error_null(tmp);
	syntax_error_code(dir, error);
	token_clear(tmp);
	return (NULL);
}

void	is_pipe_tokens(t_token *tokens, int *error, t_directory *dir)
{
	if (tokens->next == NULL)
		exit_parser_pipe(error, dir, tokens);
	else if (tokens->next->kind == TK_PIPE)
		exit_parser_pipe(error, dir, tokens);
}

void	is_redirect_token(t_token *tokens, int *error, t_directory *dir)
{
	if (tokens->next == NULL)
	{
		exit_parser_token(error, dir, tokens);
	}
	else if (tokens->next->kind == TK_LESS || tokens->next->kind == TK_GREAT
		|| tokens->next->kind == TK_DGREAT || tokens->next->kind == TK_DLESS
		|| tokens->next->kind == TK_PIPE)
	{
		exit_parser_token(error, dir, tokens);
	}
}

void	is_valid_tokens(t_token *tokens, int *error, t_directory *dir)
{
	if (tokens->kind == TK_PIPE)
		is_pipe_tokens(tokens, error, dir);
	if (tokens->kind == TK_LESS || tokens->kind == TK_GREAT
		|| tokens->kind == TK_DGREAT || tokens->kind == TK_DLESS)
		is_redirect_token(tokens, error, dir);
}
