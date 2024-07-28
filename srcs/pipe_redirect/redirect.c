/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:51:54 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/28 21:34:11 by flaghata         ###   ########.fr       */
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

void	redirect(t_redirect *redi)
{
	if (redi->type == INPUT_REDI || redi->type == OUTPUT_REDI
		|| redi->type == APPEND_OUTPUT_REDI || redi->type == HEREDOC_REDI)
	{
		redi->fd_backup = ft_dup(redi->fd);
		ft_dup2(redi->fd_file, redi->fd);
		redi->heredoc_input = "";
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
		redirect(redi);
		redi = redi->next;
	}
	return (SUCCESS);
}
