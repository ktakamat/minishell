/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:39:21 by yususato          #+#    #+#             */
/*   Updated: 2024/07/15 14:58:42 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	heredoc(t_file *file, t_env **env, int *i)
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
	if (read_heredoc(file, env, fd) == false)
		return (false);
	if (filename_change(file, new_file) == false)
		return (false);
	if (g_flag == 1)
		return (false);
	return (true);
}

char	*expand_heredoc(char *line, t_env **env)
{
	int		i;
	int		len;
	char	*set;

	i = 0;
	len = 0;
	len = cmd_len(line, env);
	set = env_insert_heredoc(line, env, len);
	return (set);
}

bool	write_heredoc(char *line, t_env **env, int fd)
{
	int		start;
	char	*new;

	start = 0;
	new = expand_heredoc(line, env);
	if (new == NULL)
	{
		write(fd, "\n", 1);
		return (false);
	}
	write(fd, new, ft_strlen(new));
	write(fd, "\n", 1);
	free(new);
	return (true);
}

bool	read_heredoc(t_file *file, t_env **env, int fd)
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
		else if (write_heredoc(line, env, fd) == false)
			break ;
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
