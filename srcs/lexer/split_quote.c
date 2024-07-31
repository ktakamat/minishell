/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:08:45 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/30 19:35:51 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	dless_dquote(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
			while (line[i] == ' ')
				i++;
			if (line[i] == '"')
			{
				i++;
				while (line[i] != '\0')
				{
					if (line[i] == '"')
						return (true);
					i++;
				}
				return (false);
			}
		}
		i++;
	}
	return (false);
}

bool	dless_squote(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
			while (line[i] == ' ')
				i++;
			if (line[i] == '\'')
			{
				i++;
				while (line[i] != '\0')
				{
					if (line[i] == '\'')
						return (true);
					i++;
				}
				return (false);
			}
		}
		i++;
	}
	return (false);
}

// char	*delete_q_line(char *line)
// {
// 	char	*new_line;
// 	int		i;
// 	int		j;
// 	bool	in_quote;
// 	char	quote_char;

// 	new_line = malloc(strlen(line) + 1);
// 	i = 0;
// 	j = 0;
// 	in_quote = false;
// 	quote_char = '\0';
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == '<' && line[i + 1] == '<')
// 		{
// 			new_line[j++] = line[i++];
// 			new_line[j++] = line[i++];
// 			while (line[i] == ' ')
// 				new_line[j++] = line[i++];
// 			if (line[i] == '"' || line[i] == '\'')
// 			{
// 				quote_char = line[i];
// 				in_quote = true;
// 				i++;
// 			}
// 		}
// 		else if (in_quote && line[i] == quote_char)
// 		{
// 			in_quote = false;
// 			i++;
// 		}
// 		else
// 			new_line[j++] = line[i++];
// 	}
// 	new_line[j] = '\0';
// 	return (new_line);
// }

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
