/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:22:10 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/24 15:53:50 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(char *line, t_token_kind kind)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (token == NULL)
		return (NULL);
	token->str = line;
	token->kind = kind;
	token->next = NULL;
	return (token);
}

t_token	*create_red_token(char **tmp, char *line)
{
	if (*line == '<')
	{
		if (line[1] == '<')
			return (create_dless_token(tmp, line));
		else
			return (create_less_token(tmp, line));
	}
	else if (*line == '>')
	{
		if (line[1] == '>')
			return (create_dgreat_token(tmp, line));
		else
			return (create_great_token(tmp, line));
	}
	exit(0);
}

int	find_squote_end(char *line)
{
	int	i;

	i = 1;
	while (line[i])
	{
		while (line[i] == '\'' && line[i + 1] == '\'')
			i += 2;
		if (line[i] == '\'')
			return (i);
		i++;
	}
	return (i);
}

int	extract_squote_content(char *line, char **set)
{
	int	i;
	int	a;

	a = 0;
	i = find_squote_end(line) + 1;
	*set = (char *)malloc(sizeof(char) * (i));
	if (*set == NULL)
		return (-1);
	while (a < i -1)
	{
		(*set)[a] = line[a];
		a++;
	}
	(*set)[i - 1] = '\0';
	return (i);
}

// int	extract_squote_content(char *line, char **set)
// {
// 	int	i;
// 	int	a;

// 	i = 1;
// 	a = 0;
// 	i++;
// 	while (line[i])
// 	{
// 		while (line[i] == '\'' && line[i + 1] == '\'')
// 			i += i + 2;
// 		if (line[i] == '\'')
// 		{
// 			i++;
// 			break ;
// 		}
// 		i++;
// 	}
// 	*set = (char *)malloc(sizeof(char) * (i + 1));
// 	if (*set == NULL)
// 		return (-1);
// 	while (a < i)
// 	{
// 		(*set)[a] = line[a];
// 		a++;
// 	}
// 	(*set)[a] = '\0';
// 	return (i);
// }

t_token	*create_squote_token(char **tmp, char *line)
{
	char	*set;
	int		i;

	i = extract_squote_content(line, &set);
	if (i == -1)
	{
		return (NULL);
	}
	*tmp = line + i;
	return (create_token (set, TK_SQUOTE));
}

// t_token	*create_dquote_token(char **tmp, char *line)
// {
// 	int		i;
// 	int		a;
// 	char	*set;

// 	i = 1;
// 	a = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\"')
// 		{
// 			i++;
// 			break ;
// 		}
// 		i++;
// 	}
// 	while (line[i] != ' ' && line[i] && line[i] != '|'
// 		&& line[i] != '<' && line[i] != '>')
// 		i++;
// 	set = (char *)malloc(sizeof(char) * (i + 1));
// 	while (a < i)
// 	{
// 		set[a] = *line;
// 		a++;
// 		line++;
// 	}
// 	set[a] = '\0';
// 	*tmp = line;
// 	if (line[i - 1] == '\"')
// 		return (create_token(set, TK_DQUOTE));
// 	else
// 		return(create_token(set, TK_GENERAL));
// }
