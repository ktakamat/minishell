/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:51:54 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/16 21:12:27 by flaghata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_redirect(t_redirect *redi)
{
	int	fd;

	if (redi->type == INPUT_REDI)
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

static char	*here_doc(t_redirect *redi)
{
	char	*add_new_line;
	char	*tmp;
	char	*line;
	char	*res;

	res = ft_strdup("");
	while (true)
	{
		line = readline("> ");
		if (line == NULL)
		{
			break ;
		}
		if (!ft_strncmp(line, redi->file_name, ft_strlen(redi->file_name)))
		{
			break ;
		}
		add_new_line = ft_strjoin(line, "\n");
		tmp = ft_strjoin(res, add_new_line);
		res = tmp;
	}
	return (res);
}

void	redirect(t_redirect *redi)
{
	if (redi->type == INPUT_REDI || redi->type == OUTPUT_REDI
		|| redi->type == APPEND_OUTPUT_REDI)
	{
		redi->fd_backup = dup(redi->fd);
		//printf("now:%d %d %s\n", redi->fd, redi->fd_backup,redi->file_name);
		dup2(redi->fd_file, redi->fd);
		redi->heredoc_input = "";
	}
	else
	{
		redi->heredoc_input = here_doc(redi);
	}
}

int	exec_redirect(t_redirect *redi, t_directory *dir, t_env **env_var)
{
	while (redi != NULL)
	{
		redi->file_name = expansion(redi->file_name, dir, env_var);
		//printf("処理:%s\n", redi->file_name);
		if (redi->type != HEREDOC_REDI)
		{
			redi->fd_file = open_redirect(redi);
			if (redi->fd_file == -1)
			{
				// print_error("minishell: No such file or directory", redi->file_name);
				dir->error.error_num = 1;
				return (FAILURE);
			}
		}
		redirect(redi);
		redi = redi->next;
	}
	return (SUCCESS);
}

void	restore_fd(t_redirect *redi)
{
	if (redi == NULL)
		return ;
	if (redi->type == HEREDOC_REDI)
		return ;
	// while (redi)
	// {
		//printf("修復 %d %d %s\n",redi->fd,redi->fd_backup,redi->file_name);
		ft_dup2(redi->fd_backup, redi->fd);
		ft_close(redi->fd_backup);
		//printf("閉じた\n");
		if (redi->next)
		{
			ft_dup2(redi->next->fd_backup, redi->next->fd);
			ft_close(redi->next->fd_backup);
		}
		//redi = redi->next;
		//printf("次\n");
	//}
	// printf("修復 %d %d %s\n",redi->fd,redi->fd_backup,redi->file_name);
	// ft_dup2(redi->fd_backup, redi->fd);
	// ft_dup2(redi->next->fd_backup, redi->next->fd);
	// printf("修復done %d %d %s\n",redi->next->fd,redi->next->fd_backup,redi->file_name);
	// ft_close(redi->fd_backup);
	// ft_close(redi->next->fd_backup);
	redi->fd_backup = -1;
}
