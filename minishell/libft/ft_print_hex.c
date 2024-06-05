/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 20:45:50 by machi             #+#    #+#             */
/*   Updated: 2024/04/25 19:52:39 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_hex(unsigned int n)
{
	int	len;

	len = 0;
	while (n)
	{
		len++;
		n /= 16;
	}
	return (len);
}

void	ft_puthex(unsigned int n, const char format)
{
	if (n < 16)
	{
		if (n <= 9)
			ft_print_char(n + '0');
		else
		{
			if (format == 'x')
				ft_print_char(n - 10 + 'a');
			if (format == 'X')
				ft_print_char(n - 10 + 'A');
		}
	}
	else
	{
		ft_puthex(n / 16, format);
		ft_puthex(n % 16, format);
	}
}

int	ft_print_hex(unsigned int n, const char format)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		ft_puthex(0, format);
		count++;
	}
	else
	{
		ft_puthex(n, format);
		count += count_hex(n);
	}
	return (count);
}
