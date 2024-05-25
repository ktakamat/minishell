/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:49:19 by ktakamat          #+#    #+#             */
/*   Updated: 2024/05/24 22:28:18 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	p_left(t_parser *parser, t_args *args, int *pipefd)
{
	close(pipefd[0]);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	check_pipe(parser->left, args);
}

void	p_right(t_parser *parser, t_args *args, int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	check_pipe(parser->right, args);
}

void	p_close(pid_t pid1, pid_t pid2, int *pipefd)
{
	int	status;

	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	// if (WIFEXITED(status))
}

void	pipe_line(t_parser *parser, t_args *args)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(pipefd);
	pid1 = fork();
	if (pid1 == 0)
		p_left(parser, args, pipefd);
	pid2 = fork();
	if (pid2 == 0)
		p_right(parser, args, pipefd);
	p_close(pid1, pid2, pipefd);
}

void	check_pipe(t_parser *parser, t_args *args)
{
	if (parser == NULL)
		return ;
	printf("check_pipe\n");
	args->argv = parser->cmd;
	printf("cmd: %s\n", parser->cmd[0]);
	if (parser->type == PIPE)
	{
		printf("pipe\n");
		pipe_line(parser, args);
	}
	else
		execute_com(args);
}



// char **parse_pipeline(char *line)
// {
// 	int count = 1;
// 	char *tmp = line;

// 	while (*tmp)
// 	{
// 		if (*tmp == '|')
// 			count++;
// 		tmp++;
// 	}
	
// 	char **commands = calloc(count + 1, sizeof(char *));
// 	if (!commands)
// 		ft_exit();
// 	char *token = ft_strtok(line, "|");
// 	int i = 0;
// 	while (token)
// 	{
// 		commands[i++] = ft_strdup(token);
// 		token = ft_strtok(NULL, "|");
// 	}
// 	commands[i] = NULL;
// 	return commands;
// }


// int main() {
// 	char* commands[] = {"/bin/pwd", "cat", NULL};
// 	pipe_line(commands);

// 	return 0;
// }
