/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:02:05 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/15 12:59:59 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	heredoc_loop(t_file *file, t_env **env)
{
	int		i;
	t_file	*current;

	current = file;
	i = 0;
	while (current != NULL)
	{
		if (current->type == HEREDOC)
		{
			if (heredoc(current, env, &i) == false)
				return (false);
		}
		else if (current->type == QUOTE_HEREDOC)
		{
			if (quote_heredoc(current, &i) == false)
				return (false);
		}
		current = current->next;
	}
	return (true);
}
