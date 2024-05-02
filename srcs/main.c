/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:58:14 by ktakamat          #+#    #+#             */
/*   Updated: 2024/05/02 17:43:13 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

// char change(char **tmp,char *line)
// {
// 	*tmp = &line[1];
// 	return ;
// }

// int main(void)
// {
// 	char *line = "Hello";

// 	printf("&line:%p,line:%p\n", &line, line);
// 	printf("&line:%p,line:%p\n", &line[1], &line[2]);

// 	change(&line, line);
// 	printf("yeeeeeee&line:%p,line:%p\n", &line, line);
// 	printf("&line:%p,line:%p\n", &line[1], &line[2]);

	
// }







#include "minishell.h"

char	*get_pass(char	*line)
{
	char	path[PATH_MAX];
	char	*str;
	char	*end;
	char	*copy;

	str = getenv("PATH");
	while (*str)
	{
		bzero(path, PATH_MAX);
		end = ft_strchr(str, ':');
		if (end)
			ft_strncpy(path, str, end - str);
		else
			ft_strlcpy(path, str, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, line, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			copy = ft_strdup(path);
			if (copy == NULL)
				return (NULL);
			return (copy);
		}
		if (end == NULL)
			return (NULL);
		str = end + 1;
	}
	return (NULL);
}

int	token_count(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**token_list(t_token *token)
{
	int		i;
	char	**args;

	i = 0;
	i = token_count(token);
	args = calloc(i + 1, sizeof(char *));
	if (!args)
		ft_error();
	i = 0;
	while (token->next != NULL)
	{
		args[i] = ft_strdup(token->str);
		i++;
		token = token->next;
	}
	return (args);
}

// t_env	*env_init(char **env)
// {
// 	t_env	*env_head;
// 	t_env	*new;
// 	int		i;

// 	while (new[i] != NULL)
// 	{
		
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	**args;
	t_token	*token;
	t_env	*enve;
	pid_t	pid;
	int		status;
	char	*path;

	// enve = env_init(env);
	using_history();
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (line)
		{
			add_history(line);
			path = get_pass(line);
			token = lexer(line);
			// node = parser(token);
			expand(token);
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				exit(0);
			}
			else if (pid == 0)
			{
				args = token_list(token);
				if (!path)
				{
					args++;
					while (*args != '\0')
					{
						ft_printf("%s\n",*args);
						args++;
					}
				}
				else if (execve(path, args, env) == -1)
				{
					perror("execve");
					exit(0);
				}
			}
				else
					wait(&status);
			free(line);
		}
	}
	exit(0);
}

// // __attribute((destructor)) static void destructor() {
// // 	system("leaks -q minishell");
// // }

// void	put_error_exit(const char *error);
// void	handle_status(int *status);

// int	main(int argc, char **argv, char **env)
// {
// 	char	*line;
// 	pid_t	pid;
// 	int		status;

// 	(void)argc;
// 	(void)argv;
// 	signalctrl();
// 	while (true)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		else
// 		{
// 			add_history(line);
// 			pid = fork();
// 			if (pid < 0)
// 				put_error_exit("failed to fork");
// 			else if (pid == 0)
// 				execute(line, env);
// 			else
// 				handle_status(&status);
// 			free(line);
// 		}
// 	}
// 	rl_clear_history();
// 	exit(0);
// }

// // __attribute((destructor)) static void destructor() {
// // 	system("leaks -q minishell");
// // }

// void	put_error_exit(const char *error)
// {
// 	perror(error);
// 	exit(1);
// }

// void	handle_status(int *status)
// {
// 	wait(status);
// 	printf("status: %d\n", *status);
// 	if (*status != 0)
// 		exit(1);
// }

// int	main(int ac, char **av, char **env)
// {
// 	char	*line;
// 	t_stack	stack;
// 	t_stack	sum;
// 	t_node	*node;
// 	pid_t	pid;
// 	int		status;
// 	char	*path;

// 	//using_history();
// 	signal(SIGINT, sig_handler);
// 	while (true)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (line)
// 		{
// 			add_history(line);
// 			path = get_pass(line);
// 			pid = fork();
// 			if (pid < 0)
// 			{
// 				perror("fork");
// 				exit(0);
// 			}
// 			else if (pid == 0)
// 			{
// 				char *args[] = {line, NULL};
				
// 				if (execve(path, args, env) == -1)
// 				{
// 					perror("execve");
// 					exit(0);
// 				}
// 			}
// 				else
// 					wait(&status);
// 			printf("%d\n",status);
// 			free(line);
			
			
// 			// stack = lexer(line);
// 			// node = stack.top;
// 			// node->next = NULL;
// 			// while (node->prev != NULL)
// 			// 	node = node->prev;
// 			// parser(node);

// 		}
// 	}
// 	exit(0);
// }

// char	*get_pass(char *line)
// {
// 	char	path[PATH_MAX];
// 	char	*str;
// 	char	*end;
// 	char	*copy;

// 	str = getenv("PATH");
// 	while (*str)
// 	{
// 		bzero(path, PATH_MAX);
// 		end = strchr(str, ':');
// 		if (end)
// 			strncpy(path, str, end - str);
// 		else
// 			strlcpy(path, str, end - str);
// 		strlcat(path, "/", PATH_MAX);
// 		strlcat(path, line, PATH_MAX);
// 		if (access(path, X_OK) == 0)
// 		{
// 			copy = ft_strdup(path);
// 			if (copy == NULL)
// 				exit(0);
// 			return (copy);
// 		}
// 		if (end == NULL)
// 			return (NULL);
// 		str = end + 1;
// 	}
// 	return (NULL);
// }
