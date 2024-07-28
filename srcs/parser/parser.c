/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:41:35 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/28 20:45:15 by flaghata         ###   ########.fr       */
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

// t_parser	*parser(t_token *tokens, t_env **env_var)
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

// 次がnullの時の離脱用関数(PIPE)
t_parser	*exit_parser_pipe(int *error, t_directory *dir, t_token *tmp)
{
	*error = 258;
	syntax_error_pipe();
	syntax_error_code(dir, error);
	token_clear(tmp);
	return (NULL);
}

// 次がnullの時の離脱用関数(TOKEN)
t_parser	*exit_parser_token(int *error, t_directory *dir, t_token *tmp)
{
	*error = 258;
	syntax_error_null(tmp);
	syntax_error_code(dir, error);
	token_clear(tmp);
	return (NULL);
}

// 入力されたパイプコマンドがおかしい時の離脱用関数
t_parser	*exit_parser_invalid_pipe_cmd(
		int *error, t_directory *dir, t_parser *node)
{
	*error = 258;
	printf(PIPE_ERROR);
	syntax_error_code(dir, error);
	destroy_parser(node);
	return (NULL);
}

// トークンがnull、もしくはリダイレクトのやつじゃない時にfalseを返し、そうでない時にtrueを返す
bool	is_redirect_token(t_token *token)
{
	if (token->next == NULL)
	{
		return (false);
	}
	if (token->kind == TK_LESS || token->kind == TK_GREAT
		|| token->kind == TK_DGREAT || token->kind == TK_DLESS)
	{
		return (true);
	}
	return (false);
}

// トークンが正常か判定する
bool	is_valid_tokens(t_token *tokens, int *error, t_directory *dir)
{
	if (tokens->kind == TK_PIPE)
	{
		if (tokens->next == NULL || tokens->next->kind == TK_PIPE)
		{
			exit_parser_pipe(error, dir, tokens);
			return (false);
		}
	}
	if (is_redirect_token(tokens))
	{
		if (is_redirect_token(tokens->next) || tokens->next->kind == TK_PIPE)
		{
			exit_parser_token(error, dir, tokens);
			return (false);
		}
	}
	return (true);
}

// putdata失敗した時の離脱関数
t_parser	*exit_parser_fail_put_data(
		int *error, t_directory *dir, t_token *tmp, t_parser *node)
{
	*error = 258;
	syntax_error_code(dir, error);
	token_clear(tmp);
	destroy_parser(node);
	return (NULL);
}

t_parser	*parser(t_token *tokens, t_directory *dir, int *error,
			t_env **env_var)
{
	t_parser	*node;
	t_token		*tmp;

	if (tokens == NULL)
		return (NULL);
	tmp = tokens;
	is_valid_tokens(tmp, error, dir);
	node = node_new();
	if (put_data(node, &tokens, env_var) == FAILURE)
		exit_parser_fail_put_data(error, dir, tmp, node);
	while (tokens != NULL && tokens->kind == TK_PIPE)
	{
		tokens = tokens->next;
		if (tokens == NULL)
			exit_parser_invalid_pipe_cmd(error, dir, node);
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
