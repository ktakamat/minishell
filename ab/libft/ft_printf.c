/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:24:29 by yususato          #+#    #+#             */
/*   Updated: 2024/07/02 17:53:01 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *fmt, ...)
{
	va_list		ap;
	size_t		i;
	ssize_t		j;

	va_start(ap, fmt);
	i = 0;
	j = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			j += ft_range(fmt[i + 1], ap);
			i++;
		}
		else
		{
			ft_putchar(fmt[i]);
			j++;
		}
		i++;
	}
	va_end(ap);
	return (j);
}

int	ft_range(int c, va_list ap)
{
	ssize_t	i;

	i = 0;
	if (c == 'd' || c == 'i')
		i = ft_process_i(va_arg(ap, int));
	else if (c == 'c')
		i = ft_process_c((char)va_arg(ap, int));
	else if (c == 'p')
	{
		i += ft_putstr("0x");
		i += ft_process_p(va_arg(ap, uintptr_t));
	}
	else if (c == 's')
		i = ft_process_s(va_arg(ap, char *));
	else if (c == 'u')
		i = ft_process_u(va_arg(ap, unsigned int));
	else if (c == 'x')
		i = ft_process_x(va_arg(ap, unsigned int), c);
	else if (c == 'X')
		i = ft_process_x(va_arg(ap, unsigned int), c);
	else if (c == '%')
		i = ft_putchar(c);
	return (i);
}

int	ft_process_u(unsigned int u)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	i = ft_putnbr_u(u);
	return (i);
}

int	ft_process_c(char c)
{
	return (ft_putchar(c));
}

int	ft_process_i(int c)
{
	int	i;
	int	j;

	j = 0;
	i = ft_putnbr_i(c);
	return (i);
}
