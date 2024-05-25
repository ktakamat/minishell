/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:29:08 by ychiba            #+#    #+#             */
/*   Updated: 2024/05/24 21:07:39 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL); // Ctrl-C
	signal(SIGQUIT, SIG_IGN); // Ctrl-\ を無視
}

t_env	*new_env_node(char *env_str)
{
	t_env	*node;
	char	*separator;
	int		name_len;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	separator = ft_strchr(env_str, '=');
	if (!separator)
	{
		free(node);
		return (NULL);
	}
	name_len = separator - env_str;
	node->env_name = malloc(name_len + 1);
	ft_strncpy(node->env_name, env_str, name_len);
	node->env_name[name_len] = '\0';
	node->env_val = strdup(separator + 1);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_env	*set_env_list(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;

	head = NULL;
	tail = NULL;
	while (*envp)
	{
		new_node = new_env_node(*envp);
		if (!new_node)
		{
			perror("Failed to create env node");
			continue ;
		}
		if (tail)
		{
			tail->next = new_node;
			new_node->prev = tail;
		}
		else
			head = new_node;
		tail = new_node;
		envp++;
	}
	return (head);
}

void	ft_free_args(t_args *args)
{
	int	i;

	i = 0;
	if (args)
	{
		if (args->argv)
		{
			while (args->argv[i] != NULL)
			{
				free(args->argv[i]);
				i++;
			}
			free(args->argv);
		}
		free(args);
	}
}

int	main_loop(void)
{
	t_token	*token;
	t_args	*args;
	t_parser	*node;
	char	*line;
	int		status;

	args = NULL;
	setup_signal_handlers();
	status = 1;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		token = lexer(line);
		expand(token);
		node = parser(token);
		args = malloc(sizeof(t_args));
		if (!args)
		{
			free(line);
			continue ;
		}
		// args->argv = node->cmd;
		// status = execute_com(args);
		// if (status != 1)
		// 	break ;
		check_pipe(node, args);
		free(line);
		ft_free_args(args);
	}
	return (status);
}

void print_env_list(t_env *env_list)
{
    t_env *current = env_list;
    while (current) {
        printf("Env Name: %s, Env Value: %s\n", current->env_name, current->env_val);
        current = current->next;
    }
}

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
	while (token != NULL)
	{
		args[i] = ft_strdup(token->str);
		printf("kaisyuusan%s\n", args[i]);
		i++;
		token = token->next;
	}
	return (args);
}

void	use_history(const char *line)
{
	static int	history_index = 0;
	if (line[0] != '\0')
	{
		add_history(line);
		history_index++;
	}
	if (history_index >= MAX_HISTORY_SIZE)
	{
		remove_history(0);
		history_index--;
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env *env_list = set_env_list(envp);
	main_loop();
	while (env_list)
	{
		t_env *next = env_list->next;
		free(env_list->env_name);
		free(env_list->env_val);
		free(env_list);
		env_list = next;
	}
	exit(0);
}


// int	main(int argc, char **argv, char **env)
// {
// 	char	*line;
// 	char	**args;
// 	t_token	*token;
// 	// t_env	*enve;
// 	pid_t	pid;
// 	int		status;
// 	char	*path;
	
// 	(void)argc;
// 	(void)argv;
// 	// enve = env_init(env);
// 	while (true)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (line)
// 		{
			
// 			use_history(line);
// 			path = get_pass(line);
// 			token = lexer(line);
// 			// node = parser(token);
// 			expand(token);
// 			pid = fork();
// 			if (pid < 0)
// 			{
// 				perror("fork");
// 				exit(0);
// 			}
// 			else if (pid == 0)
// 			{
// 				args = token_list(token);
// 				if (!path)
// 				{
// 					args++;
// 					while (*args != '\0')
// 					{
// 						ft_printf("%s\n",*args);
// 						args++;
// 					}
// 				}
// 				else if (execve(path, args, env) == -1)
// 				{
// 					perror("execve");
// 					exit(0);
// 				}
// 			}
// 				else
// 					wait(&status);
// 			free(line);
// 		}
// 	}
// 	exit(0);
// }


// int	main(int argc, char **argv, char **envp)
// {
// 	int		status;
// 	// int		i = 0;
// 	(void)argc;
// 	(void)argv;
// 	status = 0;
// 	t_env *env_list = set_env_list(envp);
// 	status = main_loop();
//     print_env_list(env_list);
//     while (env_list)
// 	{
//         t_env *next = env_list->next;
//         free(env_list->env_name);
//         free(env_list->env_val);
//         free(env_list);
//         env_list = next;
//     }
// 	return (status);
// }


