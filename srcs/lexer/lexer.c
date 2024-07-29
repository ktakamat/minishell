/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:25:57 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/29 17:02:12 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_kind(t_token *lexer, int j)
{
	t_token	*tmp;

	(void)j;
	tmp = lexer;
	while (tmp != NULL)
	{
		tmp = tmp->next;
	}
}

bool	skip_space(char **tmp, char *line)
{
	if (!(*line && (*line == ' ' || *line == '\t' || *line == '\n')))
		return (false);
	while (*line && (*line == ' ' || *line == '\t' || *line == '\n'))
		line++;
	*tmp = line;
	return (true);
}

t_token	*lexer(char *line, int *i, int *j)
{
	t_token	*lexer;
	t_token	*tmp;
	t_token	*token;
	char	*lines;
	char	*original;

	lines = remove_dollar_to_quote(line);
	original = lines;
	lexer = NULL;
	tmp = NULL;
	while (*lines != '\0' && lines)
	{
		token = create_token_from_line(&lines, i, j);
		if (!token)
			continue ;
		if (lexer == NULL)
			lexer = token;
		else
			tmp->next = token;
		tmp = token;
	}
	pipe_kind(lexer, *j);
	ft_free(original);
	return (lexer);
}

void	expand(t_token *token)
{
	while (token->next != NULL)
	{
		if (token->str[0] == '\'')
			remove_squote(token);
		else if (token->str[0] == '\"')
			remove_dquote(token);
		token = token->next;
	}
}
