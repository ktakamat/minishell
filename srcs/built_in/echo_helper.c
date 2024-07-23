/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:23:57 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/23 13:25:29 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_echo(char **str, int start_index, int m_words)
{
	int	i;

	i = start_index;
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

int	check_n_option(char *str)
{
	int	j;

	j = 1;
	while (str[j] == 'n')
		j++;
	return (str[j] == '\0');
}

int	process_n_option(char **str, int *i, int m_words, int *flag)
{
	(*flag) = 1;
	if (str[*i + 1][0] != '-')
	{
		(*i)++;
		print_echo(str, *i, m_words);
		return (SUCCESS);
	}
	(*i)++;
	return (-1);
}
