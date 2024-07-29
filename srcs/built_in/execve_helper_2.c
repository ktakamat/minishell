/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_helper_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:43:49 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/29 21:19:48 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	combine_strings(char *s1, char *s2, char *s3, char *s4)
{
	ft_strcpy(s1, s2);
	ft_strcat(s1, s3);
	ft_strcat(s1, s4);
}

static int	child_process_exec(char *command_path, char **cmds, t_env *env_vars)
{
	char	**env;

	env = env_into_list(env_vars);
	execve(command_path, cmds, env);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

int	str_error(char *str)
{
	if (ft_strchr(str, '/'))
	{
		write(STDERR_FILENO, "minishell: No such file or directory", 36);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, "\n", 1);
		return (127);
	}
	write(STDERR_FILENO, "minishell", 9);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": command not found", 19);
	write(STDERR_FILENO, "\n", 1);
	return (127);
}

static int	child_execution_hand(char *command_path, char **cmds,
			t_env *env_vars)
{
	int	status;

	if (ft_fork() == 0)
		child_process_exec(command_path, cmds, env_vars);
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (FAILURE);
	}
	return (SUCCESS);
}

int	command_path_exec(char *command_path, char **cmds, t_env *env_vars)
{
	struct stat	s;

	if (stat(command_path, &s) == 0)
	{
		if (S_ISDIR(s.st_mode))
		{
			write(STDERR_FILENO, "minishell: ", 11);
			print_error("minishell: is a directory\n", command_path);
			return (FAILURE);
		}
		else if (access(command_path, X_OK) == 0)
			return (child_execution_hand(command_path, cmds, env_vars));
	}
	return (SUCCESS);
}
