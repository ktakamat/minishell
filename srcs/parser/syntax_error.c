/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:15:54 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/26 11:40:57 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	syntax_error_null(t_token *token)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (token->next == NULL)
		ft_putstr_fd("newline", STDERR_FILENO);
	else if (token && token->next->kind == TK_PIPE)
		ft_putstr_fd("|", STDERR_FILENO);
	else if (token && token->next->kind == TK_GREAT)
		ft_putstr_fd(">", STDERR_FILENO);
	else if (token && token->next->kind == TK_LESS)
		ft_putstr_fd("<", STDERR_FILENO);
	else if (token && token->next->kind == TK_DGREAT)
		ft_putstr_fd(">>", STDERR_FILENO);
	else if (token && token->next->kind == TK_DLESS)
		ft_putstr_fd("<<", STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

void	syntax_error_pipe(void)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd("|", STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

int	syntax_error_code(t_directory *dir, int *error)
{
	if (*error == 258)
		dir->error.error_num = 258;
	*error = 0;
	return (0);
}
