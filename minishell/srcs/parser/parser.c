/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:41:35 by ktakamat          #+#    #+#             */
/*   Updated: 2024/05/24 21:45:24 by ktakamat         ###   ########.fr       */
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

t_parser	*node_new(void)
{
	t_parser	*node;

	node = ft_calloc(1, sizeof(t_parser));
	if (node == NULL)
		exit(EXIT_FAILURE);
	ft_memset(node, 0, sizeof(t_parser));
	node->type = CMD;
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

bool	put_data(t_parser *parser, t_token *token)
{
	size_t	i;

	i = 0;
	parser->cmd = ft_calloc(count_tokens(token) + 1, sizeof(char *));
	while (token != NULL && token->kind != TK_PIPE)
	{
		parser->cmd[i] = ft_strdup(token->str);
		i++;
		token = token->next;
	}
	return (true);
}

t_parser	*handle_pipe(t_token *token, t_parser *parser)
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

t_parser	*parser(t_token *tokens)
{
	// t_parser	*parser;
	t_parser	*node;

	// if (parser == NULL)
	// 	return (NULL);
	node = node_new();
	if (put_data(node, tokens) == false)
		return (NULL);
	while (tokens != NULL && tokens->kind == TK_PIPE)
	{
		printf("pipe\n");
		tokens = tokens->next;
		node = handle_pipe(tokens, node);
	}
	return (node);
}
