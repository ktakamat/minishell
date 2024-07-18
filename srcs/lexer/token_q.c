/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_q.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:20:53 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/18 20:48:08 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_redirect(char c)
{
	if (c == TK_LESS || c == TK_GREAT || c == TK_DGREAT || c == TK_DLESS)
		return (true);
	return (false);
}

int	find_closing_quote(char *line)
{
	int	i;

	i = 1;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

int	find_token_end(char *line)
{
	int	i;

	i = 0;
	while (line[i] != ' ' && line[i] && line[i] != '|'
		&& line[i] != '<' && line[i] != '>')
		i++;
	return (i);
}

char	*extract_token(char *line, int length)
{
	char	*set;
	int		a;

	a = 0;
	set = (char *)malloc(sizeof(char) * (length + 1));
	while (a < length)
	{
		set[a] = *line;
		a++;
		line++;
	}
	set[a] = '\0';
	return (set);
}

t_token	*create_dquote_token(char **tmp, char *line)
{
	int		quote_end;
	int		token_end;
	char	*set;

	quote_end = find_closing_quote(line);
	token_end = find_token_end(line + quote_end);
	set = extract_token(line, quote_end + token_end);
	*tmp = line + quote_end + token_end;
	if (set[quote_end + token_end - 1] == '\"')
		return (create_token(set, TK_DQUOTE));
	else
		return (create_token(set, TK_GENERAL));
}
