/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:34:04 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/17 16:52:30 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser	*node_new(void)
{
	t_parser	*node;

	node = ft_calloc(1, sizeof(t_parser));
	if (node == NULL)
		exit(EXIT_FAILURE);
	node->type = CMD;
	node->cmd = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
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

bool	allocate_command_memory(t_parser *parser, t_token *token)
{
	parser->cmd = ft_calloc(data_size(token) + 1, sizeof(char *));
	if (parser->cmd == NULL)
	{
		return (false);
	}
	return (true);
}

bool	process_tokens(t_parser *parser, t_token **token)
{
	size_t	i;

	i = 0;
	while (*token != NULL && (*token)->kind != TK_PIPE)
	{
		if (is_redirect((*token)->kind))
		{
			if (set_redirect(parser, token) == FAILURE)
			{
				printf(NO_FILENAME);
				return (false);
			}
			continue ;
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
