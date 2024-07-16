/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:20:40 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/11 13:15:37 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	split_space(char **tmp, char *line)
{
	if (!(*line && (*line == ' ' || *line == '\t' || *line == '\n')))
		return (false);
	while (*line && (*line == ' ' || *line == '\t' || *line == '\n'))
		line++;
	*tmp = line;
	return (true);
}

t_token	*split_pipe(char **tmp, char *line)
{
	char	*set;
	t_token	*token;

	set = ft_strdup("|");
	if (set == NULL)
		return (NULL);
	*tmp = &line[1];
	token = create_token(set, TK_PIPE, false);
	return (token);
}

t_token	*split_red(char **tmp, char *line)
{
	if (*line == '<')
	{
		*tmp += 1;
		if (line[1] == '<')
		{
			*tmp += 1;
			return (create_token(ft_strdup("<<"), TK_DLESS, false));
		}
		else
			return (create_token(ft_strdup("<"), TK_LESS, false));
	}
	else if (*line == '>')
	{
		*tmp += 1;
		if (line[1] == '>')
		{
			*tmp += 1;
			return (create_token(ft_strdup(">>"), TK_DGREAT, false));
		}
		else
			return (create_token(ft_strdup(">"), TK_GREAT, false));
	}
	return (NULL);
}

t_token	*split_other(char **tmp, char *line)
{
	char	*set;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (line[len] && (line[len] != ' ' && line[len] != '\"'
			&& line[len] != '\'' && !is_lexer_continue(line[len])))
		len++;
	set = (char *)ft_calloc(sizeof(char), len + 1);
	if (set == NULL)
		return (put_error(PARSE_ERROR, &line[i]), NULL);
	while (i < len)
	{
		set[i] = line[i];
		i++;
	}
	*tmp = &line[len];
	if (line[len] == ' ')
		return (create_token(set, TK_CMD, true));
	else
		return (create_token(set, TK_CMD, false));
}

t_token	*split_word(char **tmp, char *line)
{
	if (*line == '\'')
		return (split_squote(tmp, line));
	else if (*line == '\"')
		return (split_dquote(tmp, line));
	else
		return (split_other(tmp, line));
}
