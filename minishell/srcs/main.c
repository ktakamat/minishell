/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:45:23 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/02 20:28:15 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	cleanup(char *line, t_parser *node, t_args *args)
{
	free(line);
	if (node)
		destroy_parser(node);
	if (args)
		ft_free_args(args);
}

char	*handle_input(void)
{
	char	*line;

	line = readline("minishell$ ");
	return (line);
}

// int	main_loop(char *envp[], int *error)
// {
// 	t_token		*token;
// 	t_args		*args;
// 	t_parser	*node;
// 	char		*line;
// 	int			status;
// 	t_directory	dir;
// 	t_env		*env_var;

// 	env_var = NULL;
// 	args = NULL;
// 	setup_signal_handlers();
// 	status = 1;
// 	env_var = ready_minishell(envp, &dir);
// 	while (1)
// 	{
// 		line = readline("minishell> ");
// 		if (!line)
// 			break ;
// 		token = lexer(line);
// 		if (!token)
// 			continue ;
// 		add_history(line);
// 		expand(token);
// 		node = parser(token, error);
// 		if (!node)
// 		{
// 			dir.error.error_num = 2;
// 			*error = 0;
// 			free(line);
// 			continue ;
// 		}
// 		exe_signals(node, &dir, &env_var, error);
// 		*error = 0;
// 		args = malloc(sizeof(t_args));
// 		if (!args)
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		args->argv = node->cmd;
// 		free(line);
// 		ft_free_args(args);
// 	}
// 	return (status);
// }

int	main(int argc, char **argv, char **envp)
{
	int		error;
	t_env	*env_list;
	t_env	*next;

	(void)argv;
	env_list = set_env_list(envp);
	if (argc == 1)
		main_loop(envp, &error);
	while (env_list)
	{
		next = env_list->next;
		free(env_list->env_name);
		free(env_list->env_val);
		free(env_list);
		env_list = next;
	}
	return (0);
}
