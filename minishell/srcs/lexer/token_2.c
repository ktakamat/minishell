/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:29:49 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/16 13:58:52 by ktakamat         ###   ########.fr       */
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
