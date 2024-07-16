/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:19:03 by yususato          #+#    #+#             */
/*   Updated: 2023/05/29 14:27:36 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	space(const char *str)
{
	if (*str == '\n' || *str == '\t' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		return (1);
	else
		return (0);
}

static int	check(const char *str, int count, long answer)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		answer = answer * 10 + str[i] - '0';
		if (count == 1 && (str[i + 1] >= '0' && str[i + 1] <= '9'))
		{
			if ((answer == LONG_MAX / 10 && str[i + 1] - '0' >= LONG_MAX % 10)
				|| (answer > LONG_MAX / 10))
				return ((int)(LONG_MAX));
		}
		else if (count == -1 && (str[i + 1] >= '0' && str[i + 1] <= '9'))
		{
			if (((answer == LONG_MAX / 10
						&& str[i + 1] - '0' >= LONG_MAX % 10 + 1))
				|| (answer > LONG_MAX / 10))
				return ((int)(LONG_MIN));
		}
		i++;
	}
	return ((int)(answer * count));
}

int	ft_atoi(const char *str)
{
	int		count;
	long	answer;

	count = 1;
	answer = 0;
	while (*str != '\0' && space(str))
	{
		str++;
	}
	if (*str == '-')
	{
		count = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	answer = check(str, count, answer);
	return ((int)(answer));
}
