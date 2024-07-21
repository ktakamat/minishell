/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:49:19 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/21 21:23:31 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	p_close(int pipefd[2], pid_t pid1, pid_t pid2, t_directory *dir)
{
	int	status1;
	int	status2;

	close(pipefd[PIPE_READ]);
	close(pipefd[PIPE_WRITE]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		dir->error.error_num = WEXITSTATUS(status2);
}

static void	p_left(t_parser *parser, t_directory *dir,
		t_env **env_var, int pipefd[2])
{
	ft_close(pipefd[PIPE_READ]);
	ft_dup2(pipefd[PIPE_WRITE], STDOUT_FILENO);
	ft_close(pipefd[PIPE_WRITE]);
	if (parser->left != NULL)
	{
		execution(parser->left, dir, env_var);
	}
	exit(dir->error.error_num);
}

static void	p_right(t_parser *parser, t_directory *dir,
		t_env **env_var, int pipefd[2])
{
	ft_close(pipefd[PIPE_WRITE]);
	ft_dup2(pipefd[PIPE_READ], STDIN_FILENO);
	ft_close(pipefd[PIPE_READ]);
	if (parser->right != NULL)
		execution(parser->right, dir, env_var);
	exit(dir->error.error_num);
}

void	pipe_line(t_parser *parser, t_directory *dir, t_env **env_var)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	ft_pipe(pipefd);
	pid1 = ft_fork();
	if (pid1 == 0)
		p_left(parser, dir, env_var, pipefd);
	pid2 = ft_fork();
	if (pid2 == 0)
	{
		if (dir->error.error_num == 0)
		{
			p_right(parser, dir, env_var, pipefd);
		}
	}
	p_close(pipefd, pid1, pid2, dir);
}
