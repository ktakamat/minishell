/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:44:09 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/13 15:42:46 by flaghata         ###   ########.fr       */
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
		return ;
	if (is_builtins(node->cmd[0]))
		exec_builtin(node->cmd, dir, env_var);
	else
	{
		//printf("head %s\n",head->heredoc_input);
		printf("ｱﾞｱﾞｱﾞｱﾞｱﾞ \n");
		printf("ｱﾞｱﾞｱﾞｱﾞ   ｱﾞ \n");
			int i = 0;
		printf("ｱﾞｱﾞｱﾞｱﾞ   ｱﾞ \n");
		while(node->cmd[i] != NULL)
		{
			printf("[%s/]",node->cmd[i]);
			i++;
		}
		printf("p[%s/]",dir->path);
		if (node->redirect == NULL|| node->redirect->heredoc_input == NULL)
			execute_from_path(node->cmd, dir, env_var);
		else
		{
			printf("%s",head->heredoc_input);
			//exit(EXIT_FAILURE);
		}
	}
	printf("cat end\n");
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
