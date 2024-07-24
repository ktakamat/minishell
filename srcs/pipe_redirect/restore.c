/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:52:58 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/24 17:26:20 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	restore_fd(t_redirect *redi)
{
	if (redi == NULL)
		return ;
	// if (redi->type == HEREDOC_REDI)
	// 	return ;
	ft_dup2(redi->fd_backup, redi->fd);
	ft_close(redi->fd_backup);
	if (redi->next)
	{
		if ((redi->type == INPUT_REDI && redi->next->type != INPUT_REDI)
			|| (redi->type != INPUT_REDI && redi->next->type == INPUT_REDI))
		{
			ft_dup2(redi->next->fd_backup, redi->next->fd);
			ft_close(redi->next->fd_backup);
		}
	}
	redi->fd_backup = -1;
}
