/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:19:41 by machi             #+#    #+#             */
/*   Updated: 2024/04/25 19:03:27 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_format(va_list *ap, const char *itr)
{
	int	count;

	count = 0;
	if (*itr == 'c')
		count += ft_print_char(va_arg(*ap, int));
	else if (*itr == 's')
		count += ft_print_str(va_arg(*ap, char *));
	else if (*itr == 'd' || *itr == 'i')
		count += ft_print_nbr(va_arg(*ap, int));
	else if (*itr == 'u')
		count += ft_print_unbr(va_arg(*ap, unsigned int));
	else if (*itr == 'p')
		count += ft_print_ptr(va_arg(*ap, unsigned long long));
	else if (*itr == 'x' || *itr == 'X')
		count += ft_print_hex(va_arg(*ap, int), *itr);
	else if (*itr == '%')
		count += ft_print_char('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int			count;
	const char	*itr;
	va_list		ap;

	va_start(ap, format);
	itr = format;
	count = 0;
	while (*itr)
	{
		if (*itr == '%')
		{
			itr++;
			count += parse_format(&ap, itr);
		}
		else if (*itr != '\0')
			count += ft_print_char(*itr);
		itr++;
	}
	va_end(ap);
	return (count);
}
