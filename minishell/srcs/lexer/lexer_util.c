/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:21:52 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/16 20:56:04 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_quoted(char *cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		if (cmd[j] == '\'' || cmd[j] == '\"')
			return (true);
		j++;
	}
	return (false);
}

bool	check_word(char	*line)
{
	return (*line && !ft_strchr("|&;()\t\n",*line));
}

void	ft_error(void)
{
	printf("Error\n");
	exit(0);
}

void	remove_squote(t_token *token)
{
	char	*new;
	char	*tmp;
	int		i;

	if (token->str[0] != '\'' || token == NULL)
		return ;
	tmp = token->str;
	i = ft_strlen(token->str);
	new = ft_calloc(i - 2, sizeof(char));
	tmp++;
	i = 0;
	while (tmp[i] != '\'' && tmp[i])
	{
		new[i] = tmp[i];
		i++;
	}
	if (*tmp == '\0')
	{
		ft_error();
		free(token->str);
	}
	token->str = new;
	return ;
}

void	remove_dquote(t_token *token)
{
	char	*new;
	char	*tmp;
	int		i;

	if (token->str[0] != '\"' || token == NULL)
		return ;
	tmp = token->str;
	i = ft_strlen(token->str);
	new = ft_calloc(i - 2, sizeof(char));
	tmp++;
	i = 0;
	while (tmp[i] != '\"' && tmp[i])
	{
		new[i] = tmp[i];
		i++;
	}
	if (*tmp == '\0')
		ft_error();
	free(token->str);
	token->str = new;
	return ;
}
