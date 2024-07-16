/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:44:09 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/16 12:59:10 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtins(char *command)
{
	char	**commands;
	int		i;

	commands = ft_split("pwd cd exit env echo export unset", ' ');
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

void	exec_command(t_parser *node, t_directory *dir, t_env **env_var)
{
	t_redirect	*head;

	head = node->redirect;
	if (exec_redirect(node->redirect, dir, env_var) == FAILURE)
	{
		return ;
	}
	if (is_builtins(node->cmd[0]))
		exec_builtin(node->cmd, dir, env_var);
	else
	{
		if (!node->redirect || node->redirect->type != HEREDOC_REDI)
			execute_from_path(node->cmd, dir, env_var);
		else
		{
			head = node->redirect->next;
			if (!ft_strcmp(node->cmd[0], "cat"))
			{
				int file;
   				file = open("./tmp",  O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
				write(file, node->redirect->heredoc_input, ft_strlen(node->redirect->heredoc_input));
				close(file);
				char **a;
				a = malloc(sizeof(char *) * 3);
				a[0] = malloc(sizeof(char) * 4);
				a[1] = malloc(sizeof(char) * 4);
				a[2] = 0;
				ft_strcpy(a[0],"cat");
				ft_strcpy(a[1],"tmp");
				execute_from_path(a, dir, env_var);
				free(a[0]);
				free(a[1]);
				free(a[2]);
				free(a);
				unlink(ft_strcat(dir->path,"/tmp"));
			}
			if (!ft_strcmp(node->cmd[0], "grep"))
			{
				int file;
   				file = open("./tmp",  O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
				write(file, node->redirect->heredoc_input, ft_strlen(node->redirect->heredoc_input));
				close(file);
				char **a;
				a = malloc(sizeof(char *) * 4);
				a[0] = malloc(sizeof(char) * 5);
				a[1] = malloc(sizeof(char) * (strlen(node->cmd[1]) + 1));
				a[2] = malloc(sizeof(char) * 4);
			 	a[3] = 0;
				ft_strcpy(a[0], "grep");
				ft_strcpy(a[1], node->cmd[1]);
				ft_strcpy(a[2], "tmp");
				execute_from_path(a, dir, env_var);
				free(a[0]);
				free(a[1]);
				free(a[2]);
				free(a[3]);
				free(a);
				unlink(ft_strcat(dir->path,"/tmp"));
			}
		}
	}
	return (restore_fd(head));
}

void	execution(t_parser *parser, t_directory *dir, t_env **env_var)
{
	if (parser == NULL)
		return ;
	if (parser->type == PIPE)
		pipe_line(parser, dir, env_var);
	else
		exec_command(parser, dir, env_var);
}

int	validate_cmds(char **cmds, t_directory *dir, t_env **env_var)
{
	clean_cmds(cmds, dir, env_var);
	if (!cmds || cmds[0] == NULL || cmds[0][0] == '\0')
	{
		return (1);
	}
	return (0);
}
