/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:14:45 by yususato          #+#    #+#             */
/*   Updated: 2023/05/26 18:12:50 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	len;
	int	count;

	count = 0;
	len = 1;
	if (n == INT_MIN)
		return (11);
	else if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	if (count > 0)
	len++;
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*new;

	if (n == 0)
		return (ft_strdup("0"));
	len = ft_len(n);
	new = (char *)ft_calloc((len + 1), sizeof(char));
	if (new == NULL)
		return (NULL);
	if (n == INT_MIN)
		return (ft_memcpy(new, "-2147483648\0", 12));
	if (n < 0)
	{
		new[0] = '-';
		n *= -1;
	}
	while (n != 0)
	{
		new[--len] = n % 10 + '0';
		n /= 10;
	}
	return (new);
}
