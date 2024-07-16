/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:18:11 by yususato          #+#    #+#             */
/*   Updated: 2024/07/02 17:55:38 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_process_x(unsigned int p, int c)
{
	int	i;

	i = 0;
	if (c == 'x')
		i = ft_small(p);
	else
		i = ft_large(p);
	return (i);
}

int	ft_small(unsigned int p)
{
	int			count;
	long		a;
	const char	c[] = "0123456789abcdef";

	count = 0;
	if (p >= 16)
		count = ft_small(p / 16);
	a = p % 16;
	count += write (2, &c[a], 1);
	return (count);
}

int	ft_large(unsigned int p)
{
	int			count;
	long		a;
	const char	*c = "0123456789ABCDEF";

	count = 0;
	if (p >= 16)
		count = ft_large(p / 16);
	a = p % 16;
	count += write (2, &c[a], 1);
	return (count);
}

int	ft_process_p(uintptr_t p)
{
	long		a;
	int			count;
	const char	*c = "0123456789abcdef";

	count = 0;
	if (p >= 16)
		count += ft_process_p(p / 16);
	a = p % 16;
	count += write(2, &c[a], 1);
	return (count);
}

int	ft_process_s(char *c)
{
	int	i;

	i = 0;
	i = ft_putstr(c);
	return (i);
}
