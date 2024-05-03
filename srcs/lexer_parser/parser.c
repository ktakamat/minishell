/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:41:35 by ktakamat          #+#    #+#             */
/*   Updated: 2024/05/03 18:58:02 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_tokens(t_token *tokens)
 {

	while (tokens != NULL) 
	{
		printf("%s ", tokens->str);
		tokens = tokens->next;
	}
	printf("\n");
}

void error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void pipe_line(char* commands[])
{
	int	i;
	int num_commands = 0;
	int	stdin_fd = dup(0);
	while (commands[num_commands] != NULL)
		num_commands++;
	
	int	pipe1[2];
	pid_t pids[num_commands];

	i = 0;
	while (i < num_commands - 1)
	{
		if(pipe(pipe1) < 0)
			error_exit("pipe");
		if ((pids[i] = fork()) == 0)
		{
			dup2(pipe1[1], STDOUT_FILENO);
			close(pipe1[0]);
			close(pipe1[1]);
			execlp(commands[i], commands[i], NULL);
			error_exit("execlp");
		}
		dup2(pipe1[0], STDIN_FILENO);
		close(pipe1[0]);
		close(pipe1[1]);
		i++;
	}
	if ((pids[i] = fork()) == 0)
	{
		execlp(commands[i], commands[i], NULL);
		error_exit("execlp");
	}
	dup2(stdin_fd, STDIN_FILENO);
	i = 0;
	while(i < num_commands)
	{
		waitpid(pids[i],NULL,0);
		i++;
	}
}

int main() {
	char* commands[] = {"/bin/pwd", "cat", NULL};
	pipe_line(commands);

	return 0;
}
