/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:36:15 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/29 15:58:19 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_command(t_parser *node, t_directory *dir, t_env **env_var)
{
	if (exec_redirect(node, node->redirect, dir, env_var) == FAILURE)
		return ;
	if (node->redirect != NULL)
		return ;
	if (node->cmd[0] == NULL)
		return ;
	if (is_builtins(node->cmd[0]))
	{
		exec_builtin(node->cmd, dir, env_var);
	}
	else
	{
		execute_from_path(node->cmd, dir, env_var);
	}
}
