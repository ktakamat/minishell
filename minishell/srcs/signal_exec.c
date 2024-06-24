/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:18:45 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/24 15:19:47 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_signals(void)
{
	if (signal(SIGINT, handle_exec) == SIG_ERR)
	{
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, handle_exec) == SIG_ERR)
	{
		exit(EXIT_FAILURE);
	}
}
