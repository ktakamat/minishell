/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:12:37 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/08 20:34:41 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*allocate_quoted(char *line, char quote_kind);

t_token	*split_squote(char **tmp, char *line)
{
	int		index;
	char	*set;

	index = 0;
	set = allocate_quoted(line, '\'');
	if (set == NULL)
		return (put_error(PARSE_ERROR, &line[0]), NULL);
	while (line[index + 1] != '\0')
	{
		if (line[index + 1] == '\'')
			break ;
		set[index] = line[index + 1];
		index += 1;
	}
	set[index] = '\0';
	if (line[index + 1] == '\'')
		*tmp = &line[index + 2];
	else
		*tmp = &line[index + 1];
	if (*tmp && **tmp == ' ')
	{
		return (create_token(set, TK_SQUOTE, true));
	}
	return (create_token(set, TK_SQUOTE, false));
}

t_token	*split_dquote(char **tmp, char *line)
{
	int		index;
	char	*set;

	index = 0;
	set = allocate_quoted(line, '\"');
	if (set == NULL)
		return (put_error(PARSE_ERROR, &line[0]), NULL);
	while (line[index + 1] != '\0')
	{
		if (line[index + 1] == '\"')
			break ;
		set[index] = line[index + 1];
		index += 1;
	}
	set[index] = '\0';
	if (line[index + 1] == '\"')
		*tmp = &line[index + 2];
	else
		*tmp = &line[index + 1];
	if (*tmp && **tmp == ' ')
		return (create_token(set, TK_DQUOTE, true));
	return (create_token(set, TK_DQUOTE, false));
}

static char	*allocate_quoted(char *line, char quote_kind)
{
	char	*quoted;
	int		len;

	len = 0;
	if (line == NULL || (quote_kind != '\'' && quote_kind != '\"'))
		return (NULL);
	if (line[0] != quote_kind)
		return (NULL);
	while (line[len + 1] != '\0' && line[len + 1] != quote_kind)
		len += 1;
	quoted = (char *)malloc(sizeof(char) * (len + 1));
	if (quoted == NULL)
		return (NULL);
	return (quoted);
}
