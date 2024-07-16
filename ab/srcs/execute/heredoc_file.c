/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:45:35 by yususato          #+#    #+#             */
/*   Updated: 2024/07/15 14:21:40 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	filename_change(t_file *file, char *new_file)
{
	free(file->file_name);
	file->file_name = NULL;
	file->file_name = ft_strdup(new_file);
	if (file->file_name == NULL)
	{
		free(new_file);
		return (false);
	}
	free(new_file);
	new_file = NULL;
	return (true);
}

char	*create_check(int *i)
{
	char	*new;
	char	*tmp;

	tmp = ft_itoa(*i);
	if (tmp == NULL)
		return (NULL);
	new = ft_strjoin(HEREDOC_FILE, tmp);
	if (new == NULL)
		return (free(tmp), NULL);
	free(tmp);
	while (!access(new, F_OK))
	{
		(*i)++;
		free(new);
		tmp = ft_itoa(*i);
		if (tmp == NULL)
			return (NULL);
		new = ft_strjoin(HEREDOC_FILE, tmp);
		if (new == NULL)
			return (free(tmp), NULL);
		free(tmp);
	}
	return (new);
}

char	*create_file(int *i)
{
	int			fd;
	char		*new;

	new = create_check(i);
	if (new == NULL)
		return (NULL);
	fd = open(new, O_CREAT, 0644);
	if (fd == -1)
		return (NULL);
	close(fd);
	return (new);
}

void	free_close(char *line, int fd)
{
	free(line);
	close(fd);
}
