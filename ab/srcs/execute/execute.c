/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:28:09 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/15 16:38:58 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static void	execute_pipe(t_parser *cmd, t_env **env, char **paths);
static void	pipe_function(t_parser *cmd, t_env **env \
							, char **paths, int dup_out);
static void	pipe_action(t_parser *cmd, t_env **env, char **paths);

bool	heredoc_check_loop(t_parser *parser, t_env **env)
{
	t_parser	*current;

	current = parser;
	if (current->file != NULL)
	{
		if (heredoc_loop(current->file, env) == false)
			return (false);
	}
	return (true);
}

void	execute(char *line, t_env **env, char **paths)
{
	t_token		*lexer_head;
	t_parser	*parser_head;
	t_parser	*current;

	if (line == NULL || env == NULL)
		return ;
	lexer_head = lexer(line);
	if (lexer_head == NULL)
		return ;
	parser_head = parser(lexer_head, env);
	free_lexer(lexer_head);
	if (parser_head == NULL)
		return ;
	current = parser_head;
	if (heredoc_check_loop(current, env) == false)
		return (free_parser(parser_head));
	while (current != NULL && current->next != NULL)
		current = current->next;
	execute_pipe(current, env, paths);
	free_parser(parser_head);
}

static void	execute_pipe(t_parser *cmd, t_env **env, char **paths)
{
	pid_t	pid;

	if (cmd == NULL)
		return ;
	if (cmd->prev != NULL)
	{
		pid = safe_fork();
		if (pid == 0)
		{
			pipe_function(cmd, env, paths, 1);
			exit(g_flag);
		}
		handle_status(pid, true);
	}
	else
		execute_redirect(cmd, env, paths);
}

static void	pipe_function(t_parser *cmd, t_env **env, char **paths, int dup_out)
{
	if (dup_out != 1)
		dup2(dup_out, 1);
	if (cmd->prev != NULL)
		pipe_action(cmd, env, paths);
	else
		execute_redirect(cmd, env, paths);
}

static void	pipe_action(t_parser *cmd, t_env **env, char **paths)
{
	pid_t	pid;
	int		pipes[2];
	int		original_io[2];

	if (pipe(pipes) < 0)
		return ;
	if (save_io(&original_io[0]) < 0)
		return ;
	pid = safe_fork();
	if (pid == 0)
	{
		close(pipes[READ]);
		pipe_function(cmd->prev, env, paths, pipes[WRITE]);
		close(pipes[WRITE]);
		exit(g_flag);
	}
	close(pipes[WRITE]);
	if (dup2(pipes[READ], 0) != 0)
		return (handle_status(pid, false));
	close(pipes[READ]);
	execute_redirect(cmd, env, paths);
	if (get_back_io(&original_io[0]) < 0)
		return (handle_status(pid, false));
	handle_status(pid, false);
}
