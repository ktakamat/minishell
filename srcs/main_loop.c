/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:33:15 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/26 11:38:27 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*ready_minishell(char *envp[], t_directory *dir)
{
	t_env			*env_vars;

	setup_signals();
	if (getcwd(dir->path, sizeof(dir->path)) == NULL)
		exit(EXIT_FAILURE);
	env_vars = create_env_vars(envp, dir->path);
	dir->error.error_num = 0;
	dir->signal_received = 0;
	return (env_vars);
}

void	initialize_environment(t_env **env_var, t_directory *dir, char *envp[])
{
	*env_var = ready_minishell(envp, dir);
	setup_signal_handlers();
}

int	dir_error_num(t_directory *dir, int *error)
{
	if (*error == 2)
		dir->error.error_num = 2;
	*error = 0;
	return (0);
}

int	process_command(char *line, t_directory *dir, t_env **env_var, int *error)
{
	t_token		*token;
	t_parser	*node;
	t_args		*args;
	int			i;
	int			j;

	i = 0;
	j = 0;
	token = lexer(line, &i, &j);
	if (!token)
		return (dir_error_num(dir, error));
	add_history(line);
	node = parser(token, dir, error, env_var);
	if (!node)
	{
		destroy_parser(node);
		return (dir_error_num(dir, error));
	}
	exe_signals(node, dir, env_var, error);
	*error = 0;
	args = malloc(sizeof(t_args));
	if (!args)
		return (0);
	args->argv = node->cmd;
	ft_free(line);
	destroy_parser(node);
	ft_free(args);
	return (1);
}

int	main_loop(char *envp[], int *error)
{
	char		*line;
	int			status;
	t_directory	dir;
	t_env		*env_var;

	env_var = NULL;
	initialize_environment(&env_var, &dir, envp);
	status = 1;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			break ;
		}
		if (!process_command(line, &dir, &env_var, error))
		{
			cleanup(line, NULL, NULL);
			continue ;
		}
	}
	return (status);
}
