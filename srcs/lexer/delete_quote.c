/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:35:34 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/30 19:38:40 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_delete_q_vars(char *line, t_del_q_vars *vars)
{
	vars->new_line = malloc(strlen(line) + 1);
	vars->i = 0;
	vars->j = 0;
	vars->in_quote = false;
	vars->quote_char = '\0';
}

static void	process_delete_q_line(char *line, t_del_q_vars *vars)
{
	while (line[vars->i] != '\0')
	{
		if (line[vars->i] == '<' && line[vars->i + 1] == '<')
		{
			vars->new_line[vars->j++] = line[vars->i++];
			vars->new_line[vars->j++] = line[vars->i++];
			while (line[vars->i] == ' ')
				vars->new_line[vars->j++] = line[vars->i++];
			if (line[vars->i] == '"' || line[vars->i] == '\'')
			{
				vars->quote_char = line[vars->i];
				vars->in_quote = true;
				vars->i++;
			}
		}
		else if (vars->in_quote && line[vars->i] == vars->quote_char)
		{
			vars->in_quote = false;
			vars->i++;
		}
		else
			vars->new_line[vars->j++] = line[vars->i++];
	}
	vars->new_line[vars->j] = '\0';
}

char	*delete_q_line(char *line)
{
	t_del_q_vars	vars;

	init_delete_q_vars(line, &vars);
	process_delete_q_line(line, &vars);
	return (vars.new_line);
}
