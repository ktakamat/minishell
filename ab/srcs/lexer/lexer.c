/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:40:20 by yususato          #+#    #+#             */
/*   Updated: 2024/07/11 13:15:43 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexer_error(t_token *lexer_head, char current);

t_token	*pipe_redirect_lexer(char **tmp, char *line)
{
	if (*line == '<' || *line == '>')
		return (split_red(tmp, line));
	else if (*line == '|')
		return (split_pipe(tmp, line));
	return (NULL);
}

t_token	*lexer(char *line)
{
	t_token	*lexer;
	t_token	*tmp;
	t_token	*token;

	lexer = NULL;
	while (line && *line != '\0')
	{
		if (split_space(&line, line))
			continue ;
		else if (*line == '<' || *line == '>' || *line == '|')
			token = pipe_redirect_lexer(&line, line);
		else if (check_word(line))
			token = split_word(&line, line);
		else
			return (lexer_error(lexer, *line), NULL);
		if (lexer == NULL)
			lexer = token;
		else
			tmp->next = token;
		if (token == NULL)
			return (NULL);
		tmp = token;
	}
	return (lexer);
}

static void	lexer_error(t_token *lexer_head, char current)
{
	free_lexer(lexer_head);
	put_error(PARSE_ERROR, &current);
}
