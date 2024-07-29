/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:51:54 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/29 16:06:01 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	open_redirect(t_redirect *redi)
// {
// 	int	fd;

// 	if (redi->type == INPUT_REDI || redi->type == HEREDOC_REDI)
// 	{
// 		fd = open(redi->file_name, O_RDONLY, 0);
// 	}
// 	else if (redi->type == OUTPUT_REDI)
// 	{
// 		fd = open(redi->file_name, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
// 	}
// 	else
// 	{
// 		fd = open(redi->file_name, O_WRONLY | O_CREAT | O_APPEND, FILE_MODE);
// 	}
// 	return (fd);
// }

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
	// if (redi->type == INPUT_REDI || redi->type == OUTPUT_REDI
	// 	|| redi->type == APPEND_OUTPUT_REDI || redi->type == HEREDOC_REDI)
	// {
	// 	redi->fd_backup = ft_dup(redi->fd);
	// 	ft_dup2(redi->fd_file, redi->fd);
	// 	redi->heredoc_input = "";
	// }
// }

void	redirect(t_parser *node, t_redirect *redi, t_directory *dir, t_env **env_var)
{
	int	std_in_out[2];

	if (redi == NULL)
		return ;
	if (save_in_out(&std_in_out[0]) < 0)
		return ;
	if (redirect_in_out(redi, dir) < 0)
	{
		get_back_in_out(&std_in_out[0], dir);
		return ;
	}
	if (node->cmd[0] == NULL)
	{
		get_back_in_out(&std_in_out[0], dir);
		return ;
	}
	if (is_builtins(node->cmd[0]))
	{
		exec_builtin(node->cmd, dir, env_var);
	}
	else
	{
		execute_from_path(node->cmd, dir, env_var);
	}
	get_back_in_out(&std_in_out[0], dir);
}

int	exec_pre(t_redirect *redi, t_directory *dir, t_env **env_var)
{
	while (redi != NULL)
	{
		redi->file_name = expansion(redi->file_name, dir, env_var);
		redi = redi->next;
	}
	return (SUCCESS);
}

int	exec_redirect(t_parser *node, t_redirect *redi, t_directory *dir,
			t_env **env_var)
{
	if (exec_pre(redi, dir, env_var) == FAILURE)
	{
		dir->error.error_num = 1;
		return (FAILURE);
	}
	if (redi != NULL)
	{
		redirect(node, redi, dir, env_var);
	}
	return (SUCCESS);
}
