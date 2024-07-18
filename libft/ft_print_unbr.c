/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:32:15 by machi             #+#    #+#             */
/*   Updated: 2024/04/25 19:52:39 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_udigits(unsigned int n)
{
	int	count;

	count = 0;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

void	ft_putunbr(unsigned int n)
{
	if (0 <= n && n < 10)
		ft_print_char(n + '0');
	else if (10 <= n)
	{
		ft_putunbr(n / 10);
		ft_print_char(n % 10 + '0');
	}
}

int	ft_print_unbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		ft_putunbr(0);
		count++;
	}
	else
	{
		ft_putunbr(n);
		count += count_udigits(n);
	}
	return (count);
}
