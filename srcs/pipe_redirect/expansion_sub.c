/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:37:09 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/18 18:36:24 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	state_normal_plus(t_parse_context *ctx, t_parse_state *state)
{
	*state = STATE_NORMAL;
	(ctx->i)++;
}

void	process_dollar(t_parse_context *ctx)
{
	int		var_len;
	char	*substr;
	char	*expan;
	int		expan_len;

	var_len = get_var_length(ctx->str + ctx->i);
	substr = ft_strndup(ctx->str + ctx->i, var_len);
	if (!substr)
		exit(EXIT_FAILURE);
	expan = d_handle(substr, ctx->dir, ctx->env_var);
	if (!expan)
		exit(EXIT_FAILURE);
	expan_len = ft_strlen(expan);
	if (expan_len < MAX_BUFFER_SIZE - ctx->j)
	{
		ft_strlcpy(ctx->result + ctx->j, expan, expan_len + 1);
		ctx->j += expan_len;
		ctx->i += var_len;
	}
	ft_free(expan);
}

void	process_normal_character(t_parse_context *ctx)
{
	ctx->result[(ctx->j)++] = ctx->str[(ctx->i)++];
}

char	**search(t_env **head, char *key)
{
	t_env	*current;

	current = *head;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

char	*handle_default(char *str, t_env **head)
{
	char	*processed;

	processed = expand_and_replace(str, head);
	if (processed)
	{
		ft_free(str);
		str = processed;
	}
	else
		ft_free(str);
	return (str);
}
