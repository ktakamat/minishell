/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:52:58 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/28 21:39:54 by flaghata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	restore_fd(t_redirect *redi)
// {
// 	if (redi == NULL)
// 		return ;
// 	ft_dup2(redi->fd_backup, redi->fd);
// 	ft_close(redi->fd_backup);
// 	if (redi->next)
// 	{
// 		if ((redi->type == INPUT_REDI && redi->next->type != INPUT_REDI)
// 			|| (redi->type != INPUT_REDI && redi->next->type == INPUT_REDI))
// 		{
// 			ft_dup2(redi->next->fd_backup, redi->next->fd);
// 			ft_close(redi->next->fd_backup);
// 		}
// 	}
// 	redi->fd_backup = -1;
// }

void	dup2_and_close(t_redirect *redi)
{
	ft_dup2(redi->fd_backup, redi->fd);
	ft_close(redi->fd_backup);
}

void	restore_fd(t_redirect *redi, t_parser *node)
{
	if (redi == NULL)
		return ;
	if (node->redirect->type == HEREDOC_REDI)
	{
		while (redi)
		{
			dup2_and_close(redi);
			redi->fd_backup = -1;
			redi = redi->next;
		}
	}
	else
	{
		dup2_and_close(redi);
		if (redi->next)
		{
			if ((redi->type == INPUT_REDI && redi->next->type != INPUT_REDI)
				|| (redi->type != INPUT_REDI && redi->next->type == INPUT_REDI))
				dup2_and_close(redi);
		}
		redi->fd_backup = -1;
	}
}
