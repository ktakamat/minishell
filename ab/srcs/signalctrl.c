/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:26:42 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/14 20:53:36 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_redisplay(int signum);
static void	sigquit_handler(int signum);

void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_flag = 1;
		close(0);
	}
}

void	signal_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = signal_handler_heredoc;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	signalctrl(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sigint_redisplay);
	signal(SIGQUIT, sigquit_handler);
}

static void	sigint_redisplay(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_flag = 1;
}

static void	sigquit_handler(int signum)
{
	(void)signum;
}
