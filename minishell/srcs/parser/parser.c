/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:41:35 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/17 16:53:46 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_tokens(t_token *tokens)
	{
	while (tokens != NULL)
	{
		printf("%s ", tokens->str);
		tokens = tokens->next;
	}
	printf("\n");
}

size_t	data_size(t_token *token)
{
	size_t	size;

	size = 0;
	if (token == NULL)
		return (size);
	while (token->kind == TK_PIPE && token->next != NULL)
		token = token->next;
	while (token != NULL && token->kind != TK_PIPE)
	{
		if (is_redirect(token->kind) && token->next != NULL)
		{
			token = token->next->next;
			continue ;
		}
		size++;
		token = token->next;
	}
	return (size);
}

size_t	count_tokens(t_token *tokens)
{
	size_t	count;

	count = 0;
	while (tokens->kind == TK_PIPE && tokens->next != NULL)
		tokens = tokens->next;
	while (tokens != NULL && tokens->kind != TK_PIPE)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

bool	put_data(t_parser *parser, t_token **token)
{
	if (!allocate_command_memory(parser, *token))
		return (false);
	if (!process_tokens(parser, token))
		return (false);
	return (true);
}

// bool	put_data(t_parser *parser, t_token **token)
// {
// 	size_t	i;

// 	parser->cmd = ft_calloc(data_size((*token)) + 1, sizeof(char *));
// 	if (parser->cmd == NULL)
// 		return (false);
// 	i = 0;
// 	while (*token != NULL && (*token)->kind != TK_PIPE)
// 	{
// 		if (is_redirect((*token)->kind))
// 		{
// 			if (set_redirect(parser, token) == FAILURE)
// 			{
// 				printf(NO_FILENAME);
// 				return (false);
// 			}
// 			continue ;
// 		}
// 		else
// 			parser->cmd[i] = ft_strdup((*token)->str);
// 		if (parser->cmd[i] == NULL)
// 			return (false);
// 		i++;
// 		(*token) = (*token)->next;
// 	}
// 	parser->cmd[i] = NULL;
// 	return (true);
// }

t_parser	*parser(t_token *tokens)
{
	t_parser	*node;

	node = node_new();
	if (put_data(node, &tokens) == false)
		return (NULL);
	while (tokens != NULL)
	{
		if (tokens->kind == TK_PIPE)
		{
			tokens = tokens->next;
			node = handle_pipe(&tokens, node);
		}
		else
			tokens = tokens->next;
	}
	return (node);
}
