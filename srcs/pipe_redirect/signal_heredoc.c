/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:37:03 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/24 22:38:02 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_interrupted = 1;
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
