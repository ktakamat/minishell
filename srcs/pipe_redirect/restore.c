/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:52:58 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/29 18:48:11 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	save_in_out(int *in_out)
{
	if (in_out == NULL)
		return (-1);
	in_out[0] = dup(0);
	if (in_out[0] < 0)
		return (-1);
	in_out[1] = dup(1);
	if (in_out[1] < 0)
	{
		close(in_out[0]);
		perror("minishell");
		return (-1);
	}
	return (0);
}

int	get_back_in_out(int *in_out, t_directory *dir)
{
	if (dup2(in_out[WRITE], 1) < 0)
	{
		perror_set_flag("minishell: dup: ", dir);
		close(in_out[WRITE]);
		close(in_out[READ]);
		return (-1);
	}
	if (dup2(in_out[READ], 0) < 0)
	{
		perror_set_flag("minishell: dup: ", dir);
		close(in_out[WRITE]);
		close(in_out[READ]);
		return (-1);
	}
	close(in_out[WRITE]);
	close(in_out[READ]);
	return (0);
}

static int	redirect_in(char *file_name, t_redirect_type type, t_directory *dir)
{
	int	fd;

	if (type == INPUT_REDI || type == HEREDOC_REDI)
	{
		fd = open(file_name, O_RDONLY);
		if (fd < 0)
		{
			write(2, "minishell: ", 11);
			return (perror_set_flag(file_name, dir), -1);
		}
		if (dup2(fd, 0) < 0)
		{
			write(2, "minishell: ", 11);
			return (perror_set_flag(file_name, dir), -1);
		}
		close (fd);
	}
	return (0);
}

static int	redirect_out(char *file_name, t_redirect_type type,
			t_directory *dir)
{
	int	fd;

	fd = 0;
	if (type == OUTPUT_REDI)
	{
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (type == APPEND_OUTPUT_REDI)
	{
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (fd < 0)
	{
		write(2, "minishell: ", 11);
		return (perror_set_flag(file_name, dir), -1);
	}
	if (dup2(fd, 1) < 0)
	{
		write(2, "minishell: ", 11);
		return (perror_set_flag(file_name, dir), -1);
	}
	close (fd);
	return (0);
}

int	redirect_in_out(t_redirect *head, t_directory *dir)
{
	t_redirect		*current;
	t_redirect_type	type;

	current = head;
	while (current != NULL)
	{
		type = current->type;
		if (type == INPUT_REDI || type == HEREDOC_REDI)
		{
			if (redirect_in(current->file_name, type, dir) < 0)
				return (-1);
		}
		else if (type == OUTPUT_REDI || type == APPEND_OUTPUT_REDI)
		{
			if (redirect_out(current->file_name, type, dir) < 0)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

// void	restore_fd(t_redirect *redi)
// {
// 	if (redi == NULL)
// 		return ;
// 	ft_dup2(redi->fd_backup, redi->fd);
// 	ft_close(redi->fd_backup);
// 	if (redi->next)
// 	{
// 		if ((redi->type == INPUT_REDI && redi->next->type != INPUT_REDI)
// 			|| (redi->type != INPUT_REDI && redi->next->type == INPUT_REDI))
// 		{
// 			ft_dup2(redi->next->fd_backup, redi->next->fd);
// 			ft_close(redi->next->fd_backup);
// 		}
// 	}
// 	redi->fd_backup = -1;
// }

// void	restore_fd(t_redirect *redi, t_parser *node)
// {
// 	if (redi == NULL)
// 		return ;
// 	if (node->redirect->type == HEREDOC_REDI)
// 	{	
// 		if (redi)
// 		{
// 			ft_dup2(redi->fd_backup, redi->fd);
// 			ft_close(redi->fd_backup);
// 			redi->fd_backup = -1;
// 		}
// 	}
// 	else
// 	{
// 		ft_dup2(redi->fd_backup, redi->fd);
// 		ft_close(redi->fd_backup);
// 		if (redi->next)
// 		{
// 			if ((redi->type == INPUT_REDI && redi->next->type != INPUT_REDI)
// 				|| (redi->type != INPUT_REDI && redi->next->type == INPUT_REDI))
// 			{
// 				ft_dup2(redi->next->fd_backup, redi->next->fd);
// 				ft_close(redi->next->fd_backup);
// 			}
// 		}
// 		redi->fd_backup = -1;
// 	}
// }
