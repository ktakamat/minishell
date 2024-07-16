/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stream.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:08:32 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/11 13:15:36 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_input(char *filename, t_redirect_type type);
static int	redirect_output(char *filename, t_redirect_type type);

int	redirect_stream(t_file *file_head)
{
	t_file			*current;
	t_redirect_type	type;

	current = file_head;
	while (current != NULL)
	{
		type = current->type;
		if (type == IN_FILE || type == HEREDOC || type == QUOTE_HEREDOC)
		{
			if (redirect_input(current->file_name, type) < 0)
				return (-1);
		}
		else if (type == OUT_FILE || type == APPEND)
		{
			if (redirect_output(current->file_name, type) < 0)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

static int	redirect_input(char *filename, t_redirect_type type)
{
	int	fd;

	if (type == IN_FILE || type == HEREDOC || type == QUOTE_HEREDOC)
	{
		fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			write(2, "minishell: ", 11);
			return (perror_set_flag(filename), -1);
		}
		if (dup2(fd, 0) < 0)
		{
			write(2, "minishell: ", 11);
			return (perror_set_flag(filename), -1);
		}
		close(fd);
	}
	return (0);
}

static int	redirect_output(char *filename, t_redirect_type type)
{
	int	fd;

	fd = 0;
	if (type == OUT_FILE)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
	{
		write(2, "minishell: ", 11);
		return (perror_set_flag(filename), -1);
	}
	if (dup2(fd, 1) < 0)
	{
		write(2, "minishell: ", 11);
		return (perror_set_flag(filename), -1);
	}
	close(fd);
	return (0);
}
