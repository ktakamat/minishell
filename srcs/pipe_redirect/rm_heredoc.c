/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:16:48 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/25 17:17:44 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	tmp = ft_itoa_2(i);
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
