/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:14:44 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/28 16:44:50 by flaghata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_heredoc(char *line, t_env **env_var)
{
	char	*set;
	int		len;

	len = cmd_len(line, env_var);
	set = insert_heredoc(line, env_var, len);
	return (set);
}

bool	write_heredoc(char *line, t_env **env_var, int fd)
{
	char	*new_line;

	new_line = expand_heredoc(line, env_var);
	if (!new_line)
	{
		write(fd, "\n", 1);
		return (false);
	}
	write(fd, new_line, ft_strlen(new_line));
	write(fd, "\n", 1);
	free(new_line);
	return (true);
}

bool	read_here_doc(t_redirect *redi, t_env **env_var, int fd)
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
		if (ft_strlen(line) && is_equal(line, redi->file_name))
			break ;
		else if (write_heredoc(line, env_var, fd) == false)
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

bool	file_name_change(t_redirect *redi, char *new_file)
{
	free(redi->file_name);
	redi->file_name = NULL;
	redi->file_name = ft_strdup(new_file);
	if (!redi->file_name)
	{
		free(new_file);
		return (false);
	}
	free(new_file);
	new_file = NULL;
	return (true);
}
