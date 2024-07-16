/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:12:18 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/09 15:49:34 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	cmd_init(t_token **lexer_tmp, t_parser **parser_tmp)
{
	(*parser_tmp)->cmd = (char **)ft_calloc(2, sizeof(char *));
	if ((*parser_tmp)->cmd == NULL)
		return (false);
	(*parser_tmp)->cmd[0] = ft_strdup((*lexer_tmp)->str);
	if ((*parser_tmp)->cmd[0] == NULL)
		return (false);
	(*parser_tmp)->cmd[1] = NULL;
	return (true);
}

void	free_parser_tmp(t_parser **tmp)
{
	int	i;

	i = 0;
	while ((*tmp)->cmd[i] != NULL)
	{
		free((*tmp)->cmd[i]);
		i++;
	}
	free((*tmp)->cmd);
	return ;
}

bool	parser_tmp_insert(t_parser **parser_tmp, char **tmp, int *i)
{
	*i = 0;
	while ((*parser_tmp)->cmd[*i] != NULL)
	{
		tmp[*i] = ft_strdup((*parser_tmp)->cmd[*i]);
		if (tmp[*i] == NULL)
			return (false);
		(*i)++;
	}
	return (true);
}

bool	cmd_add(t_token **lexer_tmp, t_parser **parser_tmp, char **tmp)
{
	int	i;

	i = 0;
	if (parser_tmp_insert(parser_tmp, tmp, &i) == false)
		return (false);
	tmp[i] = ft_strdup((*lexer_tmp)->str);
	if (tmp[i] == NULL)
		return (false);
	free_parser_tmp(parser_tmp);
	(*parser_tmp)->cmd = (char **)ft_calloc((i + 2), sizeof(char *));
	if ((*parser_tmp)->cmd == NULL)
		return (false);
	i = 0;
	while (tmp[i] != NULL)
	{
		(*parser_tmp)->cmd[i] = ft_strdup(tmp[i]);
		if ((*parser_tmp)->cmd[i] == NULL)
			return (false);
		i++;
	}
	(*parser_tmp)->cmd[i] = NULL;
	free_str_list(tmp);
	return (true);
}

void	*parser_cmd(t_token **lexer_tmp, t_parser **parser_tmp)
{
	char	**tmp;
	int		i;

	i = 0;
	if ((*parser_tmp)->cmd == NULL)
	{
		if (cmd_init(lexer_tmp, parser_tmp) == false)
			return (NULL);
	}
	else
	{
		while ((*parser_tmp)->cmd[i] != NULL)
			i++;
		tmp = (char **)ft_calloc((i + 2), sizeof(char *));
		if (tmp == NULL)
			return (NULL);
		if (cmd_add(lexer_tmp, parser_tmp, tmp) == false)
			return (NULL);
	}
	return (parser_tmp);
}
