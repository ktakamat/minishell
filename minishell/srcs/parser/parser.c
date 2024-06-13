/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:41:35 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/03 20:01:25 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void parse_tokens(t_token *tokens)
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
			printf("redirect\n");
			token = token->next->next;
			continue ;
		}
		size++;
		token = token->next;
	}
	return (size);
}

t_parser	*node_new(void)
{
	t_parser	*node;

	node = ft_calloc(1, sizeof(t_parser));
	if (node == NULL)
		exit(EXIT_FAILURE);
	// ft_memset(node, 0, sizeof(t_parser));
	node->type = CMD;
	node->cmd = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
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

bool put_data(t_parser *parser, t_token **token)
{
	size_t i;

	parser->cmd = ft_calloc(data_size((*token)) + 1, sizeof(char *));
	if (parser->cmd == NULL)
		return (false);
	i = 0;
	while (*token != NULL && (*token)->kind != TK_PIPE)
	{
		printf("token->str: %s\n", (*token)->str);
		if (is_redirect((*token)->kind))
		{
			printf("redirect\n");
			if (set_redirect(parser, token) == FAILURE)
			{
				printf(NO_FILENAME);
				return (false);
			}
			continue;
		}
		else
			parser->cmd[i] = ft_strdup((*token)->str);
		if (parser->cmd[i] == NULL)
			return (false);
		i++;
		(*token) = (*token)->next;
	}
	parser->cmd[i] = NULL;
	return (true);
}

t_parser	*handle_pipe(t_token **token, t_parser *parser)
{
	t_parser	*right;
	t_parser	*left;

	left = parser;
	right = node_new();
	if (put_data(right, token) == false)
		return (NULL);
	parser = node_new();
	parser->type = PIPE;
	parser->right = right;
	parser->left = left;
	return (parser);
}

// t_parser	*parser(t_token *tokens)
// {
// 	// t_parser	*parser;
// 	t_parser	*node;

// 	// if (parser == NULL)
// 	// 	return (NULL);
// 	node = node_new();
// 	if (put_data(node, tokens) == false)
// 		return (NULL);
// 	while (tokens != NULL && tokens->kind == TK_PIPE)
// 	{
// 		printf("pipe\n");
// 		tokens = tokens->next;
// 		node = handle_pipe(tokens, node);
// 	}
// 	return (node);
// }

t_parser *parser(t_token *tokens)
{
	t_parser *node;

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



// bool	put_data(t_parser *parser, t_token *token)
// {
// 	size_t	i;

// 	i = 0;
// 	parser->cmd = ft_calloc(count_tokens(token) + 1, sizeof(char *));
// 	while (token != NULL && token->kind != TK_PIPE)
// 	{
// 		parser->cmd[i] = ft_strdup(token->str);
// 		i++;
// 		token = token->next;
// 	}
// 	return (true);
// }

// t_parser	*parser(t_token *tokens)
// {
// 	// t_parser	*parser;
// 	t_parser	*node;

// 	// if (parser == NULL)
// 	// 	return (NULL);
// 	node = node_new();
// 	if (put_data(node, tokens) == false)
// 		return (NULL);
// 	while (tokens != NULL && tokens->kind == TK_PIPE)
// 	{
// 		printf("pipe\n");
// 		tokens = tokens->next;
// 		node = handle_pipe(tokens, node);
// 	}
// 	return (node);
// }
