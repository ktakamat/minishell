/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:02:04 by ychiba            #+#    #+#             */
/*   Updated: 2024/05/25 20:41:10 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exe_chdir(t_args *args)
{
	if (args->argv[1] == NULL)
		printf("minishell: cd requires an argument\n");
	else
	{
		if (chdir(args->argv[1]) != 0)
			perror("minishell");
	}
	return (1);
}
