/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:31:42 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/14 20:42:52 by flaghata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fork_execute(char **cmds, t_directory *dir)
{
	int	status2;

	if (ft_fork() == 0)
	{
		execve(cmds[0], cmds, NULL);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{

		wait(&status2);
		if (WIFEXITED(status2))
		{
			dir->error.error_num = WEXITSTATUS(status2);
		}
		return ;
	}
}

static bool	check_fd(char **cmds, t_directory *dir)
{
	if (!check_file(cmds[0], dir))
		return (false);
	else if (!check_fd_dir(cmds[0], dir))
		return (false);
	return (true);
}

static void	signal_error(t_directory *dir)
{
	if (dir->signal_received)
	{
		dir->error.error_num = dir->signal_received;
		dir->signal_received = 0;
	}
}

void	print_error(const char *msg, const char *path)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, path, ft_strlen(path));
	write(STDERR_FILENO, "\n", 1);
}

void	execute_from_path(char **cmds, t_directory *dir, t_env **env_vars)
{
	struct stat	s;

	exec_signals();
	int i = 0;
	while (cmds[i])
	{
		printf("%d %s\n",i,cmds[i]);
		i++;
	}
	if (validate_cmds(cmds, dir, env_vars))
		return ;
	if (stat(cmds[0], &s) == 0 && ft_strchr(cmds[0], '/'))
	{

		if (S_ISDIR(s.st_mode))
		{
			print_error("minishell: is a directory", cmds[0]);
			dir->error.error_num = 126;
			return ;
		}
		else if (access(cmds[0], X_OK) == 0)
			fork_execute(cmds, dir);
		else
		{
			if (!check_fd(cmds, dir))
				return ;
		}
	}
	else
		dir->error.error_num = parsed_command_exec(cmds[0], cmds, env_vars);
	signal_error(dir);
	return ;
}
