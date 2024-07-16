/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uni.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:38:46 by yususato          #+#    #+#             */
/*   Updated: 2024/07/02 18:03:20 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_u(unsigned int nb)
{
	int		i;
	char	c;

	i = 0;
	if (nb >= 10)
	{
		i += ft_putnbr_i(nb / 10);
	}
	c = nb % 10 + '0';
	i += write(2, &c, 1);
	return (i);
}

int	ft_putnbr_i(int nb)
{
	int		i;
	char	c;

	i = 0;
	if (nb == INT_MIN)
	{
		i = write(2, "-2147483648", 11);
		return (i);
	}
	if (nb < 0)
	{
		i += write(2, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
	{
		i += ft_putnbr_i(nb / 10);
	}
	c = nb % 10 + '0';
	i += write(2, &c, 1);
	return (i);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		i = write(2, "(null)", 6);
	else
		i = write(2, s, ft_strlen(s));
	return (i);
}

int	ft_putchar(int n)
{
	return (write(2, &n, 1));
}
