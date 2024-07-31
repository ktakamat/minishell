/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:03:21 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/31 19:11:35 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_syntax(t_token *tokens, t_directory *dir, int *error)
{
	if (tokens->next == NULL)
	{
		*error = 258;
		syntax_error_pipe();
		syntax_error_code(dir, error);
		return (FAILURE);
	}
	else if (tokens->next->kind == TK_PIPE || tokens->next->kind == TK_CMD)
	{
		*error = 258;
		syntax_error_pipe();
		syntax_error_code(dir, error);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_redirection_syntax(t_token *tokens, t_directory *dir, int *error)
{
	if (tokens->next == NULL)
	{
		*error = 258;
		syntax_error_null(tokens);
		syntax_error_code(dir, error);
		return (FAILURE);
	}
	else if (tokens->next->kind == TK_LESS || tokens->next->kind == TK_GREAT
		|| tokens->next->kind == TK_DGREAT || tokens->next->kind == TK_DLESS
		|| tokens->next->kind == TK_PIPE)
	{
		*error = 258;
		syntax_error_null(tokens);
		syntax_error_code(dir, error);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	syntax_er(int *error, t_directory *dir, t_token *tmp)
{
	*error = 258;
	syntax_error_code(dir, error);
	token_clear(tmp);
}
