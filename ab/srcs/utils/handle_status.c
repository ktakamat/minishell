/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:19:08 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/14 22:25:40 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_status(pid_t pid_to_wait, bool set_flag)
{
	int	status;

	waitpid(pid_to_wait, &status, 0);
	if (WIFSIGNALED(status))
		write(1, "\n", 1);
	if (set_flag)
	{
		if (WIFEXITED(status))
			g_flag = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_flag = 128 + WTERMSIG(status);
		else
			g_flag = 1;
	}
}
