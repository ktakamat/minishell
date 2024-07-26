/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:52:58 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/26 18:43:51 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	restore_fd(t_redirect *redi)
// {
// 	if (redi == NULL)
// 		return ;
// 	ft_dup2(redi->fd_backup, redi->fd);
// 	ft_close(redi->fd_backup);
// 	redi->fd_backup = -1;
// }

// void	restore_fd(t_redirect *redi, t_parser *node)
// {
// 	if (redi == NULL)
// 		return ;
// 	if (node->redirect->type == HEREDOC_REDI)
// 	{	
// 		while (redi)
// 		{
// 			ft_dup2(redi->fd_backup, redi->fd);
// 			ft_close(redi->fd_backup);
// 			redi->fd_backup = -1;
// 			redi = redi->next;
// 		}
// 	}
// 	else
// 	{
// 		ft_dup2(redi->fd_backup, redi->fd);
// 		ft_close(redi->fd_backup);
// 		if (redi->next)
// 		{
// 			if ((redi->type == INPUT_REDI && redi->next->type != INPUT_REDI)
// 				|| (redi->type != INPUT_REDI && redi->next->type == INPUT_REDI))
// 			{
// 				ft_dup2(redi->next->fd_backup, redi->next->fd);
// 				ft_close(redi->next->fd_backup);
// 			}
// 		}
// 		redi->fd_backup = -1;
// 	}
// }

void	restore_fd(t_redirect *redi)
{
	if (redi == NULL)
		return;

	// 入力リダイレクトの復元
	if (redi->fd_backup_in != -1)
	{
		ft_dup2(redi->fd_backup_in, STDIN_FILENO);
		ft_close(redi->fd_backup_in);
		redi->fd_backup_in = -1;
	}

	// 出力リダイレクトの復元
	if (redi->fd_backup_out != -1)
	{
		ft_dup2(redi->fd_backup_out, STDOUT_FILENO);
		ft_close(redi->fd_backup_out);
		redi->fd_backup_out = -1;
	}
}
