/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychiba <ychiba@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:19:28 by ychiba            #+#    #+#             */
/*   Updated: 2024/04/29 16:24:18 by ychiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	put_exit_error(char **argv)
{
	printf("exit\n");
	printf("minishell: exit: %s: numeric argument required\n", argv[1]);
	exit (255);
}

int	check_exit_args(char **argv)
{
	int	i;

	i = 0;
	if (argv[1] == NULL)
		exit (0);
	if (argv[1][i] == '+' || argv[1][i] == '-')
		i++;
	if (argv[1][i] == '\0')
		put_exit_error(argv);
	while (argv[1][i] != '\0')
	{
		if (ft_isdigit(argv[1][i]) != 1)
			put_exit_error(argv);
		i++;
	}
	return (0);
}

int	exe_exit(t_args *args)
{
	int	status;

	status = 0;
	check_exit_args(args->argv);
	if (args->argc > 2)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	status = ft_atoi(args->argv[1]);
	printf("exit");
	if (status < 0)
	{
		status = 256 + (status % 256);
		exit (status);
	}
	exit (status % 256);
}
