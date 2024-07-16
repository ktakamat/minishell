/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:06:10 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/15 21:11:39 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		;
	g_interrupted = 1;
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_exec(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_interrupted = 130;
	}
	else if (signal == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit: 3\n", 9);
		g_interrupted = 131;
	}
}

static void	execute_reset_error(t_parser *node, t_directory *dir,
		t_env **env_vars, int *error)
{
	if (node == NULL)
	{
		if (*error == 2)
			dir->error.error_num = 2;
		if (*error == 1)
			dir->error.error_num = 1;
	}
	execution(node, dir, env_vars);
	setup_signals();
	*error = 0;
}

void	exe_signals(t_parser *node, t_directory *dir,
			t_env **env_vars, int *error)
{
	if (g_interrupted == 1)
	{
		*error = g_interrupted;
		dir->error.error_num = g_interrupted;
		g_interrupted = 0;
	}
	else if (g_interrupted == 130 || g_interrupted == 131)
	{
		dir->error.error_num = g_interrupted;
		g_interrupted = 0;
	}
	execute_reset_error(node, dir, env_vars, error);
}
