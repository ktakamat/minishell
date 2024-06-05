/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:55:21 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/05 20:55:24 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_com(t_args	*args)
{
	args->argc = 0;
	while (args->argv[args->argc] != NULL)
		args->argc++;
	if (args->argv[0] == NULL)
		return (1);
	if (ft_strncmp(args->argv[0], "exit", 5) == 0)
		return (exe_exit(args));
	if (ft_strncmp(args->argv[0], "cd", 3) == 0)
		return (exe_chdir(args));
	if (ft_strncmp(args->argv[0], "pwd", 4) == 0)
		return (exe_pwd(args));
	if (ft_strncmp(args->argv[0], "echo", 5) == 0)
		return (exe_echo(*args));
	if (ft_strncmp(args->argv[0], "env", 4) == 0)
		return (exe_env());
	// if (ft_strncmp(args->argv[0], "export", 7) == 0)
	// 	return (exe_export());
	// if (ft_strncmp(args->argv[0], "unset", 6) == 0)
	// 	return (exe_unset());
	if (ft_strncmp(args->argv[0], "grep", 3) == 0)
	{
		printf("grep\n");
		args->argv[0] = "/usr/bin/grep";
		return (execve(args->argv[0], args->argv, NULL));
	}
	if (ft_strncmp(args->argv[0], "ls", 3) == 0)
	{
		args->argv[0] = "/bin/ls";
		return (execve(args->argv[0], args->argv, NULL));
	}
	return (1);
}
