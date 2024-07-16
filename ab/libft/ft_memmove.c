/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:34:37 by yususato          #+#    #+#             */
/*   Updated: 2023/10/16 22:38:28 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *buf, const void *buf2, size_t n)
{
	size_t			i;

	if (!buf && !buf2)
		return (NULL);
	if (buf > buf2 && n != 0)
	{
		i = n - 1;
		while (i > 0)
		{
			((unsigned char *)buf)[i] = ((unsigned char *)buf2)[i];
			i--;
		}
		((unsigned char *)buf)[0] = ((unsigned char *)buf2)[0];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)buf)[i] = ((unsigned char *)buf2)[i];
			i++;
		}
	}
	return (buf);
}
