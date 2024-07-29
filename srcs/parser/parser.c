/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:41:35 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/30 07:36:39 by flaghata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	put_data(t_parser *parser, t_token **token, t_env **env_var)
{
	size_t	i;

	parser->cmd = ft_calloc(data_size(*token) + 1, sizeof(char *));
	i = 0;
	while (*token != NULL && (*token)->kind != TK_PIPE)
	{
		if (is_redirect((*token)->kind))
		{
			if (set_redirect(parser, token, env_var) == FAILURE)
			{
				printf(NO_FILENAME);
				return (FAILURE);
			}
			continue ;
		}
		else
			parser->cmd[i] = ft_strdup((*token)->str);
		if ((*token)->next != NULL)
			(*token) = (*token)->next;
		else
			break ;
		i++;
	}
	return (SUCCESS);
}

t_parser	*handle_pipe(t_token **token, t_parser *parser, t_env **env_var)
{
	t_parser	*right;
	t_parser	*left;

	left = parser;
	right = node_new();
	if (put_data(right, token, env_var) == FAILURE)
		return (destroy_parser(parser));
	parser = node_new();
	parser->type = PIPE;
	parser->right = right;
	parser->left = left;
	return (parser);
}

t_parser	*parser(t_token *tokens, t_directory *dir, int *error,
			t_env **env_var)
{
	t_parser	*node;
	t_token		*tmp;

	if (tokens == NULL)
		return (NULL);
	tmp = tokens;
	if (!is_valid_token(tmp, error, dir))
		return (NULL);
	node = node_new();
	if (put_data(node, &tokens, env_var) == FAILURE)
		return (exit_parser_fail_put_data(error, dir, tmp, node));
	while (tokens != NULL && tokens->kind == TK_PIPE)
	{
		tokens = tokens->next;
		if (tokens == NULL)
			return (exit_parser_invalid_pipe_cmd(error, dir, node));
		node = handle_pipe(&tokens, node, env_var);
		if (*error)
		{
			token_clear(tmp);
			return (NULL);
		}
	}
	token_clear(tmp);
	return (node);
}
