/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:09:50 by yususato          #+#    #+#             */
/*   Updated: 2023/05/29 18:04:43 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *buf, const void *buf2, size_t n)
{
	size_t			i;
	unsigned char	*p;

	if (!buf && !buf2)
		return (NULL);
	i = 0;
	p = (unsigned char *)buf;
	while (i < n)
	{
		p[i] = ((unsigned char *)buf2)[i];
		i++;
	}
	return (buf);
}
