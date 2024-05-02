/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 02:35:16 by machi             #+#    #+#             */
/*   Updated: 2024/04/25 19:52:39 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_ptr(uintptr_t n)
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

void	ft_putptr(uintptr_t n)
{
	if (n < 16)
	{
		if (n <= 9)
			ft_print_char(n + '0');
		else
			ft_print_char(n - 10 + 'a');
	}
	else
	{
		ft_putptr(n / 16);
		ft_putptr(n % 16);
	}
}

int	ft_print_ptr(unsigned long long ptr)
{
	int	count;

	count = 0;
	count += ft_print_str("0x");
	if (ptr == 0)
		count += ft_print_char('0');
	else
	{
		ft_putptr(ptr);
		count += count_ptr(ptr);
	}
	return (count);
}
