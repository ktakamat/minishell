/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:48:42 by yususato          #+#    #+#             */
/*   Updated: 2024/07/15 14:59:20 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	quote_heredoc(t_file *file, int *i)
{
	int		fd;
	char	*new_file;

	fd = 0;
	new_file = create_file(i);
	if (new_file == NULL)
		return (false);
	(*i)++;
	fd = open(new_file, O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (false);
	if (quote_read_heredoc(file, fd) == false)
		return (false);
	if (filename_change(file, new_file) == false)
		return (false);
	if (g_flag == 1)
		return (false);
	return (true);
}

bool	quote_read_heredoc(t_file *file, int fd)
{
	int		input;
	char	*line;

	signal_heredoc();
	input = dup(0);
	if (input < 0)
		return (false);
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strlen(line) && is_equal(line, file->file_name))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
	if (dup2(input, 0) < 0)
		return (close(input), false);
	close(input);
	return (true);
}
