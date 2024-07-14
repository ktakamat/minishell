/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:51:54 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/14 16:21:18 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_redirect(t_redirect *redi)
{
	if (redi->type == INPUT_REDI)
		return (open(redi->file_name, O_RDONLY, 0));
	if (redi->type == OUTPUT_REDI)
		return (open(redi->file_name, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE));
	return (open(redi->file_name, O_WRONLY | O_CREAT | O_APPEND, FILE_MODE));
}

static void	here_doc(t_redirect *redi, int pipefd[2])
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
			break ;
		if (!ft_strncmp(line, redi->file_name, ft_strlen(redi->file_name)))
		{
			ft_free(line);
			break ;
		}
		add_new_line = ft_strjoin(line, "\n");
		tmp = ft_strjoin(res, add_new_line);
		ft_free(res);
		ft_free(add_new_line);
		res = tmp;
		ft_free(line);
	}
	ft_putstr_fd(pipefd[PIPE_WRITE], res);
	ft_free(res);
}

void	redirect(t_redirect *redi)
{
	int	pipefd[2];
	int	backup;

	if (redi->type == INPUT_REDI || redi->type == OUTPUT_REDI
		|| redi->type == APPEND_OUTPUT_REDI)
	{
		redi->fd_backup = ft_dup(redi->fd);
		ft_dup2 (redi->fd_file, redi->fd);
		return ;
	}
	else
	{
		backup = ft_dup(STDIN_FILENO);
		ft_pipe(pipefd);
		here_doc(redi, pipefd);
		ft_dup2(pipefd[0], STDIN_FILENO);
		ft_close(pipefd[0]);
		ft_close(pipefd[1]);
		ft_dup2(backup, STDIN_FILENO);
		close(backup);
	}
}

int	exec_redirect(t_redirect *redi, t_directory *dir, t_env **env_var)
{
	while (redi != NULL)
	{
		redi->file_name = expansion(redi->file_name, dir, env_var);
		if (redi->type != HEREDOC_REDI)
		{
			redi->fd_file = open_redirect(redi);
			if (redi->fd_file == -1)
			{
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
	ft_dup2(redi->fd_backup, STDOUT_FILENO);
	ft_close(redi->fd_backup);
	redi->fd_backup = -1;
}
