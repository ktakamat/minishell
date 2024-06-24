/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:06:10 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/24 14:02:02 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_interrupted = 0;

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

void	setup_signals(void)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		exit(EXIT_FAILURE);
	}
}
