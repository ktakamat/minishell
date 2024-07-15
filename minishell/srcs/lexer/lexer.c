/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:25:57 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/14 12:18:33 by flaghata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_kind(t_token *lexer, int j)
{
	t_token	*tmp;
	int		i;

	(void)j;
	i = 0;
	tmp = lexer;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
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

int	first_pipe(char *str, int *error)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
	{
		printf(PIPE_ERROR);
		*error = 2;
		return (2);
	}
	return (0);
}

/// @brief  トークんのリスト作成
t_token	*lexer(char *line, int *error)
{
	t_token	*lexer;
	t_token	*tmp;
	t_token	*token;
	int		i;
	int		j;

	lexer = NULL;
	tmp = NULL;
	i = 0;
	j = 0;
	if (first_pipe(line, error) == 2)
		return (NULL);
	while (*line != '\0' && line)
	{
		token = create_token_from_line(&line, &i, &j);
		// if (token && token->str)
		// 	printf("!%s\n",token->str);
		if (!token)
			continue ;
		if (lexer == NULL)
			lexer = token;
		else
			tmp->next = token;
		tmp = token;
	}
	pipe_kind(lexer, j);
	return (lexer);
}

/// @brief  ""消す
/// @param token 入力の種類
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

/// リダイレクトか
bool	is_redirect(char c)
{
	if (c == TK_LESS || c == TK_GREAT || c == TK_DGREAT || c == TK_DLESS)
		return (true);
	return (false);
}
