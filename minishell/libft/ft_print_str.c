/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:51:17 by machi             #+#    #+#             */
/*   Updated: 2024/04/25 19:52:39 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(char *str)
{
	int		count;
	char	*str_null;

	count = 0;
	str_null = "(null)";
	if (!str)
	{
		while (*str_null)
		{
			count += ft_print_char(*str_null);
			str_null++;
		}
	}
	else
	{
		while (*str)
		{
			count += ft_print_char(*str);
			str++;
		}
	}
	return (count);
}
