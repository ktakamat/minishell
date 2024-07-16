/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:16:09 by yususato          #+#    #+#             */
/*   Updated: 2024/07/15 14:11:29 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_heredoc_loop(int *i, char *file, char *tmp)
{
	while (!access(file, F_OK))
	{
		unlink(file);
		free(file);
		file = NULL;
		(*i)++;
		tmp = ft_itoa(*i);
		if (tmp == NULL)
			return ;
		file = ft_strjoin(HEREDOC_FILE, tmp);
		free(tmp);
		tmp = NULL;
		if (file == NULL)
			return ;
	}
	free(file);
}

void	rm_heredoc_file(void)
{
	int		i;
	char	*file;
	char	*tmp;

	i = 0;
	tmp = ft_itoa(i);
	if (tmp == NULL)
		return ;
	file = ft_strjoin(HEREDOC_FILE, tmp);
	if (file == NULL)
	{
		free(tmp);
		return ;
	}
	free(tmp);
	rm_heredoc_loop(&i, file, tmp);
	return ;
}
