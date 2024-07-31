/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:41:35 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/31 19:11:45 by ktakamat         ###   ########.fr       */
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

// t_parser	*parser(t_token *tokens, t_directory *dir, int *error,
// 			t_env **env_var)
// {
// 	t_parser	*node;
// 	t_token		*tmp;

// 	if (tokens == NULL)
// 		return (NULL);
// 	tmp = tokens;
// 	if (tokens->kind == TK_PIPE)
// 	{
// 		if (check_pipe_syntax(tokens, dir, error) == FAILURE)
// 			return (token_clear(tmp), NULL);
// 	}
// 	if (tokens->kind == TK_LESS || tokens->kind == TK_GREAT
// 		|| tokens->kind == TK_DGREAT || tokens->kind == TK_DLESS)
// 	{
// 		if (check_redirection_syntax(tokens, dir, error) == FAILURE)
// 			return (token_clear(tmp), NULL);
// 	}
// 	node = node_new();
// 	if (put_data(node, &tokens, env_var) == FAILURE)
// 		return (handle_syntax_error(error, dir, tmp), destroy_parser(node));
// 	while (tokens != NULL && tokens->kind == TK_PIPE)
// 	{
// 		tokens = tokens->next;
// 		if (tokens == NULL)
// 		{
// 			handle_syntax_error(error, dir, tmp);
// 			printf(P_E);
// 			return (destroy_parser(node));
// 		}
// 		node = handle_pipe(&tokens, node, env_var);
// 		if (*error)
// 			return (token_clear(tmp), NULL);
// 	}
// 	return (token_clear(tmp), node);
// }

t_parser	*parser(t_token *tokens, t_directory *dir, int *er,
				t_env **env_var)
{
	t_parser	*node;
	t_token		*tmp;

	tmp = tokens;
	if (!tokens)
		return (NULL);
	if (tokens->kind == TK_PIPE && pipe_syntax(tokens, dir, er) == FAILURE)
		return (token_clear(tmp), NULL);
	if ((tokens->kind == TK_LESS || tokens->kind == TK_GREAT
			|| tokens->kind == TK_DGREAT || tokens->kind == TK_DLESS)
		&& check_redirection_syntax(tokens, dir, er) == FAILURE)
		return (token_clear(tmp), NULL);
	node = node_new();
	if (put_data(node, &tokens, env_var) == FAILURE)
		return (syntax_er(er, dir, tmp), destroy_parser(node));
	while (tokens && tokens->kind == TK_PIPE)
	{
		tokens = tokens->next;
		if (!tokens)
			return (syntax_er(er, dir, tmp), printf(P_E), destroy_parser(node));
		node = handle_pipe(&tokens, node, env_var);
		if (*er)
			return (token_clear(tmp), NULL);
	}
	return (token_clear(tmp), node);
}
