/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:03:09 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/24 23:21:20 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTORY_H
# define DIRECTORY_H

# define PATH_MAX 1024
# include "./minishell.h"

typedef struct s_error
{
	int	error_num;
}	t_error;

typedef struct s_directory
{
	char		path[PATH_MAX];
	int			signal_received;
	t_error		error;
}	t_directory;

#endif
