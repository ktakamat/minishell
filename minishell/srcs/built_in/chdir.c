/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:55:14 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/05 20:55:17 by ktakamat         ###   ########.fr       */
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
