/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychiba <ychiba@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:54:06 by ychiba            #+#    #+#             */
/*   Updated: 2024/04/29 16:27:51 by ychiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exe_echo(t_args args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args.argv[i] && strcmp(args.argv[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args.argv[i])
	{
		printf("%s", args.argv[i]);
		if (args.argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (1);
}
