/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:50:15 by yususato          #+#    #+#             */
/*   Updated: 2024/07/14 14:04:52 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	expand_cmd(t_token *tmp, t_env **env)
{
	int		i;
	int		len;
	char	*set;

	i = 0;
	len = 0;
	len = cmd_len(tmp->str, env);
	set = env_insert(tmp->str, env, len);
	free(tmp->str);
	tmp->str = set;
	return (true);
}

bool	expand_dquote(t_token *tmp, t_env **env)
{
	int		len;
	char	*set;

	len = 0;
	len = cmd_len(tmp->str, env);
	set = env_insert(tmp->str, env, len);
	if (set == NULL)
		return (false);
	free(tmp->str);
	tmp->str = set;
	return (true);
}

bool	expand(t_token *lexer, t_env **env)
{
	t_token	*tmp;

	tmp = lexer;
	while (tmp != NULL)
	{
		if (tmp->kind == TK_DLESS && tmp->next != NULL)
			tmp = tmp->next;
		else if (tmp->kind == TK_CMD)
		{
			if (expand_cmd(tmp, env) == false)
				return (false);
		}
		else if (tmp->kind == TK_DQUOTE)
		{
			if (expand_dquote(tmp, env) == false)
				return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}
