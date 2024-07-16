/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:27:58 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/13 09:28:30 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(t_env *env)
{
	char	**path_list;
	char	*path_line;

	if (env == NULL)
		return (NULL);
	path_line = _getenv(env, "PATH");
	if (path_line == NULL)
		return (NULL);
	path_list = ft_split(path_line, ':');
	free(path_line);
	return (path_list);
}
