/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:44:16 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/14 16:49:29 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
