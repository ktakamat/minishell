/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:51:54 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/26 18:58:13 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_redirect(t_redirect *redi)
{
	int	fd;

	if (redi->type == INPUT_REDI || redi->type == HEREDOC_REDI)
	{
		fd = open(redi->file_name, O_RDONLY, 0);
	}
	else if (redi->type == OUTPUT_REDI)
	{
		fd = open(redi->file_name, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
	}
	else
	{
		fd = open(redi->file_name, O_WRONLY | O_CREAT | O_APPEND, FILE_MODE);
	}
	return (fd);
}

bool	here_doc(t_redirect *redi, t_env **env_var)
{
	int		i;
	int		fd;
	char	*new_file;

	i = 0;
	fd = 0;
	new_file = make_file(&i);
	if (new_file == NULL)
		return (false);
	i++;
	fd = open(new_file, O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (false);
	if (read_here_doc(redi, env_var, fd) == false)
		return (false);
	if (file_name_change(redi, new_file) == false)
		return (false);
	if (g_interrupted == 1)
		return (false);
	return (true);
}

// void	redirect(t_redirect *redi)
// {
// 	if (redi->type == INPUT_REDI || redi->type == OUTPUT_REDI
// 		|| redi->type == APPEND_OUTPUT_REDI || redi->type == HEREDOC_REDI)
// 	{
// 		redi->fd_backup = ft_dup(redi->fd);
// 		ft_dup2(redi->fd_file, redi->fd);
// 		close(redi->fd_file);
// 		redi->heredoc_input = "";
// 	}
// }

void	redirect(t_redirect *redi)
{
	if (redi->type == INPUT_REDI || redi->type == HEREDOC_REDI)
	{
		redi->fd_backup_in = ft_dup(STDIN_FILENO);
		ft_dup2(redi->fd_file, STDIN_FILENO);
		close(redi->fd_file);
		if (redi->type == HEREDOC_REDI)
			redi->heredoc_input = "";
	}
	else if (redi->type == OUTPUT_REDI || redi->type == APPEND_OUTPUT_REDI)
	{
		redi->fd_backup_out = ft_dup(STDOUT_FILENO);
		ft_dup2(redi->fd_file, STDOUT_FILENO);
		close(redi->fd_file);
	}
}


int	exec_pre(t_redirect *redi, t_directory *dir, t_env **env_var)
{
	while (redi != NULL)
	{
		redi->file_name = expansion(redi->file_name, dir, env_var);
		if (redi->type != HEREDOC_REDI)
		{
			redi->fd_file = open_redirect(redi);
			if (redi->fd_file == -1)
			{
				return (FAILURE);
			}
		}
		redi = redi->next;
	}
	return (SUCCESS);
}

// int	exec_redirect(t_redirect *redi, t_directory *dir, t_env **env_var)
// {
// 	if (exec_pre(redi, dir, env_var) == FAILURE)
// 	{
// 		dir->error.error_num = 1;
// 		return (FAILURE);
// 	}
// 	while (redi != NULL)
// 	{
// 		redi->file_name = expansion(redi->file_name, dir, env_var);
// 		redi->fd_file = open_redirect(redi);
// 		if (redi->fd_file == -1)
// 		{
// 			dir->error.error_num = 1;
// 			return (FAILURE);
// 		}
// 		if (redi->fd_backup != -1)
// 			restore_fd(redi);
// 		redirect(redi);
// 		redi = redi->next;
// 	}
// 	return (SUCCESS);
// }

int	exec_redirect(t_redirect *redi, t_directory *dir, t_env **env_var)
{
	if (exec_pre(redi, dir, env_var) == FAILURE)
	{
		dir->error.error_num = 1;
		return (FAILURE);
	}
	while (redi != NULL)
	{
		redi->file_name = expansion(redi->file_name, dir, env_var);
		redi->fd_file = open_redirect(redi);
		if (redi->fd_file == -1)
		{
			dir->error.error_num = 1;
			return (FAILURE);
		}
		if (redi->fd_backup_in == -1 || redi->fd_backup_out == -1)
		{
			restore_fd(redi);
		}
		redirect(redi);
		redi = redi->next;
	}
	return (SUCCESS);
}
