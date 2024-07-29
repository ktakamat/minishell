/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_d_q.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:17:47 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/29 18:28:02 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*remove_dollar_to_quote(const char *input)
// {
// 	int		length;
// 	char	*result;
// 	int		i;
// 	int		j;

// 	length = strlen(input);
// 	result = malloc(length + 1);
// 	i = 0;
// 	j = 0;
// 	while (i < length)
// 	{
// 		if (input[i] == '$')
// 		{
// 			result[j++] = '$';
// 			i++;
// 			if (input[i] == '?')
// 			{
// 				result[j++] = '?';
// 				i++;
// 			}
// 			else if (input[i] == '"')
// 			{
// 				result[j++] = '"';
// 				i++;
// 				while (i < length && input[i] != '"')
// 					result[j++] = input[i++];
// 				if (i < length && input[i] == '"')
// 				{
// 					result[j++] = '"';
// 					i++;
// 				}
// 			}
// 			else
// 			{
// 				while (i < length && input[i] != ' '
// 					&& input[i] != '"' && input[i] != '$')
// 					result[j++] = input[i++];
// 			}
// 		}
// 		else
// 			result[j++] = input[i++];
// 	}
// 	result[j] = '\0';
// 	return (result);
// }

static int	handle_dollar_case(const char *input, char *result, int *i, int *j)
{
	result[(*j)++] = '$';
	(*i)++;
	if (input[*i] == '?')
	{
		result[(*j)++] = '?';
		(*i)++;
	}
	else if (input[*i] == '"')
	{
		result[(*j)++] = '"';
		(*i)++;
		while (input[*i] != '\0' && input[*i] != '"')
			result[(*j)++] = input[(*i)++];
		if (input[*i] == '"')
			result[(*j)++] = input[(*i)++];
	}
	else
	{
		while (input[*i] != '\0' && input[*i] != ' ' && input[*i] != '"'
			&& input[*i] != '$')
			result[(*j)++] = input[(*i)++];
	}
	return (0);
}

char	*remove_dollar_to_quote(const char *input)
{
	int		length;
	int		i;
	int		j;
	char	*result;

	length = strlen(input);
	result = malloc(length + 1);
	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '$')
			handle_dollar_case(input, result, &i, &j);
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}
