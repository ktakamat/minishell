/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:55:54 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/05 20:55:57 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exe_pwd(t_args *args)
{
	char	*cwd;

	cwd = (char *)malloc(PATH_MAX);
	if (cwd == NULL)
		return (1);
	if (args->argc > 1)
	{
		printf("pwd has no option.\n");
		return (1);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		free(cwd);
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (1);
}
