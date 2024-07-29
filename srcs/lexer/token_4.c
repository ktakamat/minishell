/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:23:09 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/30 07:37:46 by flaghata         ###   ########.fr       */
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

t_parser	*exit_parser_fail_put_data(
		int *error, t_directory *dir, t_token *tmp, t_parser *node)
{
	*error = 258;
	syntax_error_code(dir, error);
	token_clear(tmp);
	destroy_parser(node);
	return (NULL);
}

t_parser	*exit_parser_invalid_pipe_cmd(
		int *error, t_directory *dir, t_parser *node)
{
	*error = 258;
	printf(PIPE_ERROR);
	syntax_error_code(dir, error);
	destroy_parser(node);
	return (NULL);
}

bool	is_valid_token(t_token *tokens, int *error, t_directory *dir)
{
	if (tokens->kind == TK_PIPE)
	{
		if (tokens->next == NULL || tokens->next->kind == TK_PIPE
			|| tokens->next->kind == TK_CMD)
		{
			exit_parser_pipe(error, dir, tokens);
			return (false);
		}
	}
	if (tokens->kind == TK_LESS || tokens->kind == TK_GREAT
		|| tokens->kind == TK_DGREAT || tokens->kind == TK_DLESS)
	{
		if (tokens->next == NULL || tokens->next->kind == TK_LESS
			|| tokens->next->kind == TK_GREAT || tokens->next->kind == TK_DGREAT
			|| tokens->next->kind == TK_DLESS || tokens->next->kind == TK_PIPE)
		{
			exit_parser_pipe(error, dir, tokens);
			return (false);
		}
	}
	return (true);
}
