/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:44:16 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/13 22:56:02 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	exe_echo(t_args args)
// {
// 	int	i;
// 	int	newline;

// 	i = 1;
// 	newline = 1;
// 	if (args.argv[i] && strcmp(args.argv[i], "-n") == 0)
// 	{
// 		newline = 0;
// 		i++;
// 	}
// 	while (args.argv[i])
// 	{
// 		printf("%s", args.argv[i]);
// 		if (args.argv[i + 1])
// 			printf(" ");
// 		i++;
// 	}
// 	if (newline)
// 		printf("\n");
// 	return (1);
// }

static void	helper_echo(char **str, int m_words)
{
	int	i;

	i = 1;
	while (i < m_words)
	{
		printf("%s ", str[i]);
		i++;
	}
	printf("%s", str[i]);
	printf("\n");
}

int	exec_echo(char **str, int m_words)
{
	int	i;

	i = 1;
	if (str[1] == NULL)
	{
		printf("\n");
		return (SUCCESS);
	}
	if (ft_memcmp(str[1], "-n", 3) == 0)
	{
		i++;
		while (i < m_words)
		{
			printf("%s ", str[i]);
			i++;
		}
		if (str[i])
		{
			printf("%s", str[i]);
		}
	}
	else
		helper_echo(str, m_words);
	return (SUCCESS);
}
