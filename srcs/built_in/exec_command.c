/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:36:15 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/18 20:44:09 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc_cat(t_redirect *redirect, t_directory *dir,
			t_env **env_var)
{
	int		file;
	char	**args;

	file = open("./tmp", O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	write(file, redirect->heredoc_input, strlen(redirect->heredoc_input));
	close(file);
	args = malloc(sizeof(char *) * 3);
	args[0] = strdup("cat");
	args[1] = strdup("tmp");
	args[2] = NULL;
	execute_from_path(args, dir, env_var);
	free(args[0]);
	free(args[1]);
	free(args);
	unlink(strcat(dir->path, "/tmp"));
}

void	handle_heredoc_grep(t_parser *node, t_redirect *redirect,
				t_directory *dir, t_env **env_var)
{
	int		file;
	char	**args;

	file = open("./tmp", O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	write(file, redirect->heredoc_input, strlen(redirect->heredoc_input));
	close(file);
	args = malloc(sizeof(char *) * 4);
	args[0] = strdup("grep");
	args[1] = strdup(node->cmd[1]);
	args[2] = strdup("tmp");
	args[3] = NULL;
	execute_from_path(args, dir, env_var);
	free(args[0]);
	free(args[1]);
	free(args[2]);
	free(args);
	unlink(strcat(dir->path, "/tmp"));
}

void	handle_heredoc(t_parser *node, t_redirect *redirect,
					t_directory *dir, t_env **env_var)
{
	if (!strcmp(node->cmd[0], "cat"))
		handle_heredoc_cat(redirect, dir, env_var);
	else if (!strcmp(node->cmd[0], "grep"))
		handle_heredoc_grep(node, redirect, dir, env_var);
}

void	exec_command(t_parser *node, t_directory *dir, t_env **env_var)
{
	t_redirect	*head;

	head = node->redirect;
	if (exec_redirect(node->redirect, dir, env_var) == FAILURE)
		return ;
	if (is_builtins(node->cmd[0]))
		exec_builtin(node->cmd, dir, env_var);
	else if (!node->redirect || node->redirect->type != HEREDOC_REDI)
		execute_from_path(node->cmd, dir, env_var);
	else
		handle_heredoc(node, node->redirect, dir, env_var);
	restore_fd(head);
}
