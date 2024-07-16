/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:18:16 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/15 17:36:56 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_error_efd(t_code error_code, char *insert);

void	perror_set_flag(char *insert)
{
	if (insert == NULL || *insert == '\0')
		write(2, ":", 1);
	perror(insert);
	g_flag = 1;
}

void	put_error(t_code error_code, char *insert)
{
	if (error_code == EXPORT_ERROR || error_code == UNSET_ERROR)
	{
		write_error_efd(error_code, insert);
		g_flag = 1;
	}
	else if (error_code == NOT_FOUND_ERROR)
	{
		write_error_efd(error_code, insert);
		g_flag = 127;
	}
	else if (error_code == PARSE_ERROR)
	{
		write_error_efd(error_code, insert);
		g_flag = 258;
	}
	else if (error_code == PARSE_ERROR_REDIRECT_STR)
	{
		write_error_efd(error_code, insert);
		g_flag = 258;
	}
	else if (error_code == PARSE_ERROR_REDIRECT)
	{
		write(2, "minishell: syntax error near unexpected 'newline'\n", 50);
		g_flag = 258;
	}
}

void	put_error_exit(t_code error_code)
{
	if (error_code == FORK_ERROR)
		write(2, "fork failed: resource temporarily unavailable\n", 46);
	exit(149);
}

static void	write_error_efd(t_code e_code, char *insert)
{
	char	*error_message;

	error_message = NULL;
	if (e_code == EXPORT_ERROR)
		error_message = join_three_strs("minishell: export: `", insert, \
										"': not a valid identifier\n");
	else if (e_code == UNSET_ERROR)
		error_message = join_three_strs("minishell: unset: `", insert, \
										"': not a valid identifier\n");
	else if (e_code == NOT_FOUND_ERROR)
		error_message = join_three_strs("minishell: ", insert, \
									": command not found\n");
	else if (e_code == PARSE_ERROR)
		error_message = join_three_strs(\
		"minishell: syntax error near unexpected token `", insert, "'\n");
	else if (e_code == PARSE_ERROR_REDIRECT_STR)
		error_message = join_three_strs(\
		"minishell: syntax error near unexpected token `", insert, "'\n");
	else
		return ;
	write(2, error_message, ft_strlen(error_message));
	free(error_message);
}
