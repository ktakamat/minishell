/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:44:16 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/23 13:24:24 by ktakamat         ###   ########.fr       */
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

int	handle_non_n_option(char **str, int i, int m_words, int flag)
{
	if (flag == 1)
	{
		print_echo(str, i, m_words);
	}
	else
	{
		helper_echo(str, m_words);
	}
	return (SUCCESS);
}

int	handle_n_option(char **str, int *i, int m_words)
{
	int	flag;
	int	result;

	flag = 0;
	while (str[*i][0] == '-')
	{
		if (!check_n_option(str[*i]))
		{
			return (handle_non_n_option(str, *i, m_words, flag));
		}
		else
		{
			result = process_n_option(str, i, m_words, &flag);
			if (result != -1)
				return (result);
		}
	}
	return (-1);
}

int	process_options_and_print(char **str, int m_words)
{
	int	i;
	int	result;

	i = 1;
	result = handle_n_option(str, &i, m_words);
	if (result != -1)
		return (result);
	helper_echo(str, m_words);
	return (SUCCESS);
}

int	exec_echo(char **str, int m_words)
{
	if (str[1] == NULL)
	{
		printf("\n");
		return (SUCCESS);
	}
	return (process_options_and_print(str, m_words));
}

// int	print_echo(char **str, int start_index, int m_words)
// {
// 	int	i;

// 	i = start_index;
// 	while (i < m_words)
// 	{
// 		write(1, str[i], strlen(str[i]));
// 		write(1, " ", 1);
// 		i++;
// 	}
// 	if (str[i])
// 	{
// 		write(1, str[i], strlen(str[i]));
// 	}
// }

// int	exec_echo(char **str, int m_words)
// {
// 	int		i;
// 	int		j;
// 	int		flag;

// 	i = 1;
// 	j = 1;
// 	flag = 0;
// 	if (str[1] == NULL)
// 	{
// 		printf("\n");
// 		return (SUCCESS);
// 	}
// 	while (str[i][0] == '-')
// 	{
// 		j = 1;
// 		while (str[i][j] == 'n')
// 			j++;
// 		if (str[i][j] != '\0' && str[i][j] != 'n')
// 		{
// 			if (flag == 1)
// 			{
// 				print_echo(str, i, m_words);
// 				return (SUCCESS);
// 			}
// 			else
// 			{
// 				j = 0;
// 				helper_echo(str, m_words);
// 				return (SUCCESS);
// 			}
// 		}
// 		else
// 		{
// 			flag = 1;
// 			if (str[i + 1][0] != '-')
// 			{
// 				i++;
// 				print_echo(str, i, m_words);
// 				return (SUCCESS);
// 			}
// 			else
// 				i++;
// 		}
// 	}
// 	helper_echo(str, m_words);
// 	return (SUCCESS);
// }

// int	exec_echo(char **str, int m_words)
// {
// 	int	i;

// 	i = 1;
// 	if (str[1] == NULL)
// 	{
// 		printf("\n");
// 		return (SUCCESS);
// 	}
// 	if (ft_memcmp(str[1], "-n", 3) == 0)
// 	{
// 		i++;
// 		while (i < m_words)
// 		{
// 			write(1, str[i], strlen(str[i]));
// 			write(1, " ", 1);
// 			i++;
// 		}
// 		if (str[i])
// 		{
// 			write(1, str[i], strlen(str[i]));
// 		}
// 	}
// 	else
// 		helper_echo(str, m_words);
// 	return (SUCCESS);
// }
