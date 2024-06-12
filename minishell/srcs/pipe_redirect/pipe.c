/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:49:19 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/11 16:03:58 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	p_left(t_parser *parser, t_args *args, int *pipefd)
// {
// 	close(pipefd[0]);
// 	dup2(pipefd[1], 1);
// 	close(pipefd[1]);
// 	check_pipe(parser->left, args);
// }

// void	p_right(t_parser *parser, t_args *args, int *pipefd)
// {
// 	close(pipefd[1]);
// 	dup2(pipefd[0], 0);
// 	close(pipefd[0]);
// 	check_pipe(parser->right, args);
// }

// void	p_close(pid_t pid1, pid_t pid2, int *pipefd)
// {
// 	int	status;

// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, &status, 0);
// 	// if (WIFEXITED(status))
// }

// void	pipe_line(t_parser *parser, t_args *args)
// {
// 	int		pipefd[2];
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	pipe(pipefd);
// 	pid1 = fork();
// 	if (pid1 == 0)
// 		p_left(parser, args, pipefd);
// 	pid2 = fork();
// 	if (pid2 == 0)
// 		p_right(parser, args, pipefd);
// 	p_close(pid1, pid2, pipefd);
// }

static void	p_close(int pipefd[2], pid_t pid1, pid_t pid2, t_directory *dir)
{
	int	status1;
	int	status2;

	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		dir->error.error_num = WEXITSTATUS(status2);
}

static void	p_left(t_parser *parser, t_directory *dir,
		t_env **env_var, int pipefd[2])
{
	close(pipefd[0]);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	if (parser->left != NULL)
		execution(parser->left, dir, env_var);
	exit(dir->error.error_num);
}

static void	p_right(t_parser *parser, t_directory *dir,
		t_env **env_var, int pipefd[2])
{
	ft_close(pipefd[1]);
	ft_dup2(pipefd[0], 0);
	ft_close(pipefd[0]);
	if (parser->right != NULL)
		execution(parser->right, dir, env_var);
	exit(dir->error.error_num);
}

void	pipe_line(t_parser *parser, t_directory *dir, t_env **env_var)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(pipefd);
	pid1 = fork();
	if (pid1 == 0)
		p_left(parser, dir, env_var, pipefd);
	pid2 = ft_fork();
	if (pid2 == 0)
		p_right(parser, dir, env_var, pipefd);
	p_close(pipefd, pid1, pid2, dir);
}
