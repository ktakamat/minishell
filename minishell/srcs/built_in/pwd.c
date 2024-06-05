/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychiba <ychiba@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:09:28 by ychiba            #+#    #+#             */
/*   Updated: 2024/04/29 15:23:04 by ychiba           ###   ########.fr       */
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
