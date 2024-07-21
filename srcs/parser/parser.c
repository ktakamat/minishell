/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:41:35 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/21 22:29:25 by ktakamat         ###   ########.fr       */
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

static int	put_data(t_parser *parser, t_token **token)
{
	size_t	i;

	parser->cmd = ft_calloc(data_size(*token) + 1, sizeof(char *));
	i = 0;
	while (*token != NULL && (*token)->kind != TK_PIPE)
	{
		if (is_redirect((*token)->kind))
		{
			if (set_redirect(parser, token) == FAILURE)
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

t_parser	*handle_pipe(t_token **token, t_parser *parser, int *error)
{
	t_parser	*right;
	t_parser	*left;

	left = parser;
	if (*token == NULL)
	{
		printf(PIPE_ERROR);
		*error = 2;
		return (destroy_parser(parser));
	}
	right = node_new();
	if (put_data(right, token) == FAILURE)
		return (destroy_parser(parser));
	parser = node_new();
	parser->type = PIPE;
	parser->right = right;
	parser->left = left;
	return (parser);
}


// t_parser	*parser(t_token *tokens, int *error)
// {
// 	t_parser	*node;
// 	t_token		*tmp;

// 	if (tokens == NULL)
// 		return (NULL);
// 	tmp = tokens;
// 	node = node_new();
// 	if (put_data(node, &tokens) == FAILURE)
// 		return (destroy_parser(node));
// 	if (tokens->kind == TK_LESS || tokens->kind == TK_GREAT
// 		|| tokens->kind == TK_DGREAT || tokens->kind == TK_DLESS)
// 	{
// 		if (tokens->next->kind == TK_LESS || tokens->next->kind == TK_GREAT
// 			|| tokens->next->kind == TK_DGREAT
// 			|| tokens->next->kind == TK_DLESS)
// 		{
// 			put_syntax_error(tokens);
// 			token_clear(tmp);
// 			return (NULL);
// 		}
// 	}
// 	while (tokens != NULL && tokens->kind == TK_PIPE)
// 	{
// 		tokens = tokens->next;
// 		node = handle_pipe(&tokens, node, error);
// 		if (*error)
// 		{
// 			token_clear(tmp);
// 			return (NULL);
// 		}
// 	}
// 	token_clear(tmp);
// 	return (node);
// }

void	syntax_error_null(t_token *token)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (token && token->next->kind == TK_PIPE)
		ft_putstr_fd("|", STDERR_FILENO);
	else if (token && token->next->kind == TK_GREAT)
		ft_putstr_fd(">", STDERR_FILENO);
	else if (token && token->next->kind == TK_LESS)
		ft_putstr_fd("<", STDERR_FILENO);
	else if (token && token->next->kind == TK_DGREAT)
		ft_putstr_fd(">>", STDERR_FILENO);
	else if (token && token->next->kind == TK_DLESS)
		ft_putstr_fd("<<", STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

t_parser	*parser(t_token *tokens, int *error)
{
	t_parser	*node;
	t_token		*tmp;

	if (tokens == NULL)
		return (NULL);
	tmp = tokens;
	while (tokens->kind == TK_LESS || tokens->kind == TK_GREAT
		|| tokens->kind == TK_DGREAT || tokens->kind == TK_DLESS)
	{
		if (tokens->next->kind == TK_LESS || tokens->next->kind == TK_GREAT
			|| tokens->next->kind == TK_DGREAT
			|| tokens->next->kind == TK_DLESS)
		{
			syntax_error_null(tokens);
			*error = 1;
			token_clear(tmp);
			return (NULL);
		}
	}
	node = node_new();
	if (put_data(node, &tokens) == FAILURE)
		return (destroy_parser(node));
	while (tokens != NULL && tokens->kind == TK_PIPE)
	{
		tokens = tokens->next;
		node = handle_pipe(&tokens, node, error);
		if (*error)
		{
			token_clear(tmp);
			return (NULL);
		}
	}
	token_clear(tmp);
	return (node);
}