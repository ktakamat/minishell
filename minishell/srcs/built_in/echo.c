/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:44:16 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/14 18:08:37 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	helper_echo(char **str, int m_words)
{
	int	i;

	i = 1;
	while (i < m_words)
	{
		write(1, str[i], strlen(str[i]));
		write(1, " ", 1);
		i++;
	}
	write(1, str[i], strlen(str[i]));
	write(1, "\n", 1);
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
			write(1, str[i], strlen(str[i]));
			write(1, " ", 1);
			i++;
		}
		if (str[i])
		{
			write(1, str[i], strlen(str[i]));
		}
	}
	else
		helper_echo(str, m_words);
	return (SUCCESS);
}
