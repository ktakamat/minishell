/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machi <machi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:03:09 by ktakamat          #+#    #+#             */
/*   Updated: 2024/04/09 15:45:21 by machi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(const char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\f' || c == '\r' || c == '\v')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

long	ft_long(const char *str, int sign)
{
	long	num;
	size_t	i;

	num = 0;
	i = 0;
	while ('0' <= str[i] && str[i] <= '9' && str[i] != '\0')
	{
		if (sign == 1)
		{
			if ((num == LONG_MAX / 10 && str[i] > LONG_MAX % 10 + '0')
				|| (num > LONG_MAX / 10))
				return (LONG_MAX);
		}
		else
		{
			if ((-1 * num == LONG_MIN / 10 && -1
					* (str[i] - '0') < (LONG_MIN % 10))
				|| (-1 * num < LONG_MIN / 10))
				return (LONG_MIN);
		}
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	return (sign * num);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				is_negative;

	is_negative = 1;
	i = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_negative *= -1;
		i++;
	}
	return (ft_long(&str[i], is_negative));
}
