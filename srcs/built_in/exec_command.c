/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:36:15 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/28 21:36:37 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_command(t_parser *node, t_directory *dir, t_env **env_var)
{
	t_redirect	*head;

	head = node->redirect;
	if (exec_redirect(node, node->redirect, dir, env_var) == FAILURE)
		return ;
	if (node->cmd[0] == NULL)
		return ;
	write(1, "exec_command\n", 13);
	if (is_builtins(node->cmd[0]))
	{
		write(1, "exec_builtin\n", 13);
		exec_builtin(node->cmd, dir, env_var);
	}
	else
	{
		write(1, "exec_from_path\n", 15);
		execute_from_path(node->cmd, dir, env_var);
	}
}
