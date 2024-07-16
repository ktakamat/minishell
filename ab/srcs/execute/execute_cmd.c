/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:43:54 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/15 16:42:50 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_execve(char **cmd, t_env *env, char **paths);
static void	execute_path(char *path, char **cmd, char **env);
static bool	is_dir(char *path);

void	execute_cmd(char **cmd, t_env **env, char **paths)
{
	if (cmd == NULL || cmd[0] == NULL || env == NULL)
		return ;
	if (is_equal(cmd[0], "echo") == 1)
		return (_echo(cmd));
	else if (is_equal(cmd[0], "cd") == 1)
		return (_cd(cmd, *env));
	else if (is_equal(cmd[0], "pwd") == 1)
		return (_pwd());
	else if (is_equal(cmd[0], "export") == 1)
		return (_export(cmd, env));
	else if (is_equal(cmd[0], "unset") == 1)
		return (_unset(cmd, env));
	else if (is_equal(cmd[0], "env") == 1)
		return (_env(*env, false));
	else if (is_equal(cmd[0], "exit") == 1)
		return (minishell_exit(cmd));
	else
		execute_execve(cmd, *env, paths);
}

static void	execute_execve(char **cmd, t_env *env, char **paths)
{
	char	**env_str;

	if (cmd == NULL || cmd[0] == NULL)
		return ;
	env_str = env_into_list(env);
	if (paths != NULL && ft_strchr(cmd[0], '/') == NULL)
		execute_envpath(paths, cmd, env_str);
	else
		execute_path(cmd[0], cmd, env_str);
	free_str_list(env_str);
}

static void	execute_path(char *path, char **cmd, char **env)
{
	pid_t	pid;

	if (cmd == NULL)
		return ;
	pid = safe_fork();
	if (pid == 0)
	{
		if (is_dir(path) == true)
			errno = EISDIR;
		else if (execve(path, cmd, env) != -1)
			exit(0);
		write(2, "minishell: ", 11);
		perror(cmd[0]);
		if (errno == EACCES)
			exit(126);
		else if (errno == EISDIR)
			exit(126);
		else if (errno == ENOENT)
			exit(127);
		else
			exit(EXIT_FAILURE);
	}
	handle_status(pid, true);
}

static bool	is_dir(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) < 0)
		return (false);
	if (S_ISDIR(path_stat.st_mode))
		return (true);
	return (false);
}
