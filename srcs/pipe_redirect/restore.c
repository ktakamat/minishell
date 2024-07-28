/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:52:58 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/28 19:57:30 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redirect_in(char *file_name, t_redirect_type type, t_directory *dir);
static int	redirect_out(char *file_name, t_redirect_type type, t_directory *dir);

int	save_in_out(int *in_out)
{
	write(1, "save_in_out1\n", 13);
	if (in_out == NULL)
		return (-1);
	write(1, "save_in_out2\n", 13);
	in_out[0] = dup(0);
	write(1, "save_in_out3\n", 13);
	if (in_out[0] < 0)
		return (-1);
	write(1, "save_in_out4\n", 13);
	in_out[1] = dup(1);
	write(1, "save_in_out5\n", 13);
	if (in_out[1] < 0)
	{
		write(1, "save_in_out6\n", 13);
		close(in_out[0]);
		perror("minishell");
		return (-1);
	}
	write(1, "save_in_out7\n", 13);
	return (0);
}

int	get_back_in_out(int *in_out, t_directory *dir)
{
	write(1, "get_back_in_out1\n", 17);
	if (dup2(in_out[WRITE], 1) < 0)
	{
		write(1, "get_back_in_out2\n", 17);
		perror_set_flag("minishell: dup: ", dir);
		close(in_out[WRITE]);
		close(in_out[READ]);
		return (-1);
	}
	write(1, "get_back_in_out3\n", 17);
	if (dup2(in_out[READ], 0) < 0)
	{
		write(1, "get_back_in_out4\n", 17);
		perror_set_flag("minishell: dup: ", dir);
		close(in_out[WRITE]);
		close(in_out[READ]);
		return (-1);
	}
	write(1, "get_back_in_out5\n", 17);
	close(in_out[WRITE]);
	close(in_out[READ]);
	return (0);
}

int	redirect_in_out(t_redirect *head, t_directory *dir)
{
	t_redirect		*current;
	t_redirect_type	type;

	write(1, "redirect_in_out1\n", 17);
	current = head;
	while (current != NULL)
	{
		write(1, "redirect_in_out2\n", 17);
		type = current->type;
		if (type == INPUT_REDI || type == HEREDOC_REDI)
		{
			write(1, "redirect_in_out3\n", 17);
			if (redirect_in(current->file_name, type, dir) < 0)
				return (-1);
			write(1, "redirect_in_out3.5\n", 19);
		}
		else if (type == OUTPUT_REDI || type == APPEND_OUTPUT_REDI)
		{
			write(1, "redirect_in_out4\n", 17);
			if (redirect_out(current->file_name, type, dir) < 0)
				return (-1);
			write(1, "redirect_in_out4.5\n", 19);
		}
		current = current->next;
		write(1, "redirect_in_out5\n", 17);
	}
	write(1, "redirect_in_out6\n", 17);
	return (0);
}

static int	redirect_in(char *file_name, t_redirect_type type, t_directory *dir)
{
	int	fd;

	write(2, "redirect_in1\n", 13);
	if (type == INPUT_REDI || type == HEREDOC_REDI)
	{
		write(2, "redirect_in2\n", 13);
		fd = open(file_name, O_RDONLY);
		if (fd < 0)
		{
			write(1, "redirect_in3\n", 13);
			write(2, "minishell: ", 11);
			return (perror_set_flag(file_name, dir), -1);
		}
		if (dup2(fd, 0) < 0)
		{
			write(1, "redirect_in4\n", 13);
			write(2, "minishell: ", 11);
			return (perror_set_flag(file_name, dir), -1);
		}
		write(1, "redirect_in5\n", 13);
		close (fd);
	}
	write(1, "redirect_in6\n", 13);
	return (0);
}

static int	redirect_out(char *file_name, t_redirect_type type,
			t_directory *dir)
{
	int	fd;

	write(1, "redirect_out1\n", 14);
	fd = 0;
	if (type == OUTPUT_REDI)
	{
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write(1, "redirect_out2\n", 14);
	}
	else if (type == APPEND_OUTPUT_REDI)
	{
		write(1, "redirect_out3\n", 14);
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (fd < 0)
	{
		write(1, "redirect_out4\n", 14);
		write(2, "minishell: ", 11);
		return (perror_set_flag(file_name, dir), -1);
	}
	if (dup2(fd, 1) < 0)
	{
		write(1, "redirect_out5\n", 14);
		write(2, "minishell: ", 11);
		return (perror_set_flag(file_name, dir), -1);
	}
	close (fd);
	write(1, "redirect_out6\n", 14);
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
