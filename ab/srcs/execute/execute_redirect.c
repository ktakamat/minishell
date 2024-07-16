/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:22 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/15 16:39:59 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_redirect(t_parser *cmd, t_env **env, char **paths)
{
	int	std_io[2];

	if (cmd == NULL || env == NULL)
		return ;
	if (cmd->file == NULL)
		return (execute_cmd(cmd->cmd, env, paths));
	if (save_io(&std_io[0]) < 0)
		return ;
	if (redirect_stream(cmd->file) < 0)
	{
		get_back_io(&std_io[0]);
		return ;
	}
	execute_cmd(cmd->cmd, env, paths);
	get_back_io(&std_io[0]);
}
