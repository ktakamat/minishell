/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:55:29 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/05 20:55:31 by ktakamat         ###   ########.fr       */
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
