/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:49:41 by ychiba            #+#    #+#             */
/*   Updated: 2024/06/03 20:45:34 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_com(t_args	*args)
{
	args->argc = 0;
	while (args->argv[args->argc] != NULL)
		args->argc++;
	if (args->argv[0] == NULL)
		return (1);
	if (ft_strncmp(args->argv[0], "exit", 5) == 0)
		return (exe_exit(args));
	if (ft_strncmp(args->argv[0], "cd", 3) == 0)
		return (exe_chdir(args));
	if (ft_strncmp(args->argv[0], "pwd", 4) == 0)
		return (exe_pwd(args));
	if (ft_strncmp(args->argv[0], "echo", 5) == 0)
		return (exe_echo(*args));
	if (ft_strncmp(args->argv[0], "env", 4) == 0)
		return (exe_env());
	// if (ft_strncmp(args->argv[0], "export", 7) == 0)
	// 	return (exe_export());
	// if (ft_strncmp(args->argv[0], "unset", 6) == 0)
	// 	return (exe_unset());
	if (ft_strncmp(args->argv[0], "grep", 3) == 0)
	{
		printf("grep\n");
		args->argv[0] = "/usr/bin/grep";
		return (execve(args->argv[0], args->argv, NULL));
	}
	if (ft_strncmp(args->argv[0], "ls", 3) == 0)
	{
		args->argv[0] = "/bin/ls";
		return (execve(args->argv[0], args->argv, NULL));
	}
	return (1);
}

bool	is_builtins(char *command)
{
	char	**commands;
	int		i;

	commands = ft_split("ls grep echo cd pwd export unset env exit", ' ');
	i = 0;
	while (commands[i])
	{
		if (ft_strlen(command) != ft_strlen(commands[i]))
		{
			ft_free(commands[i]);
			i++;
			continue ;
		}
		if (ft_strcmp(command, commands[i]) == 0)
		{
			while (commands[i])
				ft_free(commands[i++]);
			ft_free(commands);
			return (true);
		}
		ft_free(commands[i]);
		i++;
	}
	ft_free(commands);
	return (false);
}

// void	exec_command(t_parser *parser, t_directory *dir, t_env **env_var)
// {
// 	t_redirect	*head;
	
// 	printf("parser->cmd[0]: %s\n", parser->cmd[0]);
// 	printf("dir->path: %s\n", dir->path);
// 	head = parser->redirect;
// 	if (exec_redirect(parser->redirect, dir, env_var) == FAILURE)
// 	{
// 		printf("exec_redirect failed\n");
// 		return ;
// 	}
// 	if (is_builtins(parser->cmd[0]))
// 	{
// 		printf("builtins\n");
// 		t_args	args;
// 		args.argv = parser->cmd;
// 		args.argc = 0;
// 		while (args.argv[args.argc] != NULL)
// 			args.argc++;
// 		printf("args.argc: %d\n", args.argc);
// 		if (execute_com(&args) == 1)
// 			return ;
// 	}
// 	return (restore_fd(head));
// }
void exec_command(t_parser *parser, t_directory *dir, t_env **env_var)
{
    t_redirect *head;

    printf("Entering exec_command\n");
    printf("parser->cmd[0]: %s\n", parser->cmd[0]);
    printf("dir->path: %s\n", dir->path[0] ? dir->path : "NULL");
    head = parser->redirect;

    // デバッグ出力: リダイレクトリストの内容を表示
    t_redirect *current = head;
    while (current != NULL)
    {
        printf("Redirect: type=%d, filename=%s\n", current->type, current->file_name);
        current = current->next;
    }

    if (exec_redirect(parser->redirect, dir, env_var) == FAILURE)
    {
        printf("exec_redirect failed\n");
        return;
    }
    
    if (is_builtins(parser->cmd[0]))
    {
        printf("Builtins detected\n");
        t_args args;
        args.argv = parser->cmd;
        args.argc = 0;
        while (args.argv[args.argc] != NULL)
            args.argc++;
        printf("args.argc: %d\n", args.argc);
        if (execute_com(&args) == 1)
            return;
	}
    return (restore_fd(head));
}

void	execution(t_parser *parser, t_directory *dir, t_env **env_var)
{
	if (parser == NULL)
		return ;
	if (parser->type == NODE_PIPE)
		pipe_line(parser, dir, env_var);
	else
		exec_command(parser, dir, env_var);
}
