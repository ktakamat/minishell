/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:51:54 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/15 16:40:01 by ktakamat         ###   ########.fr       */
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
		dup2(redi->fd_file, redi->fd);
		redi->heredoc_input = "";
	}
	else
	{
		printf("Here document redirection\n");
		redi->heredoc_input = here_doc(redi);
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
