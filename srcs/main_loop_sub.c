/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:13:06 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/29 16:13:17 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dir_error_num(t_directory *dir, int *error)
{
	if (*error == 2)
		dir->error.error_num = 2;
	*error = 0;
	return (0);
}

int	exit_command(int *error, t_directory *dir, t_parser	*node)
{
	destroy_parser(node);
	return (dir_error_num(dir, error));
}
