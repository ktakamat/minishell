/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:25:57 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/19 21:02:48 by ktakamat         ###   ########.fr       */
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
char	*remove_dollar_to_quote(const char *input)
{
	int		length;
	char	*result;
	int		i;
	int		j;

	length = strlen(input);
	result = malloc(length + 1);
	i = 0;
	j = 0;
	while (i < length)
	{
		if (input[i] == '$')
		{
			result[j++] = '$';
			i++;
			if (input[i] == '?')
			{
				result[j++] = '?';
				i++;
			}
			else if (input[i] == '"')
			{
				result[j++] = '"';
				i++;
				while (i < length && input[i] != '"')
					result[j++] = input[i++];
				if (i < length && input[i] == '"')
				{
					result[j++] = '"';
					i++;
				}
			}
			else
			{
				while (i < length && input[i] != ' '
					&& input[i] != '"' && input[i] != '$')
					result[j++] = input[i++];
			}
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

t_token	*lexer(char *line, int *error)
{
	t_token	*lexer;
	t_token	*tmp;
	t_token	*token;
	int		i;
	int		j;

	char *lines = remove_dollar_to_quote(line);
	lexer = NULL;
	tmp = NULL;
	i = 0;
	j = 0;
	if (first_pipe(lines, error) == 2)
		return (NULL);
	while (*lines != '\0' && lines)
	{
		token = create_token_from_line(&lines, &i, &j);
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
