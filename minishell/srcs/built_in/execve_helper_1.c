/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_helper_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:41:15 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/14 20:56:38 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_file(char *path, t_directory *dir)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
	{
		write(STDERR_FILENO, "minishell: No such file or directory", 36);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		dir->error.error_num = 127;
		return (false);
	}
	if ((statbuf.st_mode & S_IRUSR) == 0)
	{
		write(STDERR_FILENO, "minishell: Permission denied", 28);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		dir->error.error_num = 126;
		return (false);
	}
	return (true);
}

bool	check_fd_dir(char *path, t_directory *dir)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	if (fd > 0)
	{
		write(STDERR_FILENO, "minishell: command not found", 28);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, "\n", 1);
		ft_close(fd);
		dir->error.error_num = 127;
		return (false);
	}
	ft_close(fd);
	return (true);
}

static int	helper_exec(char *args[PATH_MAX],
				char **cmds, t_env **env_vars)
{
	char	command_path[PATH_MAX];
	char	**path_dirs;
	int		i;
	int		exec_status;

	path_dirs = search(env_vars, "PATH");
	if (path_dirs == NULL)
	{
		printf("%s: No such file or directory\n", args[0]);
		return (FAILURE);
	}
	i = 0;
	while (path_dirs[i])
	{
		combine_strings(command_path, path_dirs[i], "/", args[0]);
		exec_status = command_path_exec(command_path, cmds);
		if (exec_status != SUCCESS)
			return (exec_status);
		if (access(command_path, X_OK) == 0)
		{
			return (SUCCESS);
		}
		i++;
	}
	return (str_error(args[0]));
}

int	parsed_command_exec(char *command, char **cmds, t_env **env_vars)
{
	char	command_buffer[PATH_MAX];
	char	*command_name;
	char	*args[PATH_MAX];
	int		args_count;

	ft_strlcpy(command_buffer, command, ft_strlen(command) + 1);
	command_name = ft_strtok(command_buffer, " ");
	args_count = 0;
	while (command_name != NULL)
	{
		args[args_count] = command_name;
		command_name = ft_strtok(NULL, " ");
		args_count++;
	}
	args[args_count] = NULL;
	return (helper_exec(args, cmds, env_vars));
}
