/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:35:31 by yususato          #+#    #+#             */
/*   Updated: 2023/06/01 17:43:41 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	if (!s1 && !s2)
		return (0);
	if (n == 0)
		return (0);
	while (*p1 == *p2 && i + 1 < n)
	{
		p1++;
		p2++;
		i++;
	}
	if (*p1 != *p2)
		return (*p1 - *p2);
	else
		return (0);
}
