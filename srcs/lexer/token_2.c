/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:29:49 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/24 21:48:01 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_word_token(char **tmp, char *line)
{
	char	*set;
	int		i;

	if (*line == '\'')
	{
		return (create_squote_token(tmp, line));
	}
	else if (*line == '\"')
	{
		return (create_dquote_token(tmp, line));
	}
	i = 0;
	while (line[i] != ' ' && line[i] && line[i] != '|'
		&& line[i] != '<' && line[i] != '>')
		i++;
	set = (char *)ft_calloc(sizeof(char), i + 1);
	i = 0;
	while (line[i] != ' ' && line[i] && line[i] != '|'
		&& line[i] != '<' && line[i] != '>')
	{
		set[i] = line[i];
		i++;
	}
	*tmp = &line[i];
	return (create_token(set, TK_CMD));
}

bool	soro_redirect(char *line, int *error)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if ((line[i] == '>' || line[i] == '<') && line[i + 1] == '\0')
	{
		printf("syntax error near unexpected token `newline'\n");
		*error = 258;
		return (false);
	}
	else if (((line[i] == '>' && line[i + 1] == '>')
			|| (line[i] == '<' && line[i + 1] == '<')) && line[i + 2] == '\0')
	{
		printf("syntax error near unexpected token `newline'\n");
		*error = 258;
		return (false);
	}
	return (true);
}

t_token	*create_token_from_line(char **line, int *i, int *j)
{
	t_token	*token;

	token = NULL;
	if (skip_space(line, *line))
	{
		return (NULL);
	}
	else if (**line == '<' || **line == '>')
		token = create_red_token(line, *line);
	else if (**line == '|')
	{
		*j = *i;
		token = create_pipe_token(line, *line);
	}
	else if (check_word(*line))
		token = create_word_token(line, *line);
	else
		ft_error();
	(*i)++;
	return (token);
}

t_token	*create_pipe_token(char **tmp, char *line)
{
	char	*set;
	t_token	*token;

	set = ft_strdup("|");
	*tmp = &line[1];
	token = create_token(set, TK_PIPE);
	return (token);
}
