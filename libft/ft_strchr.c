/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:14:14 by ktakamat          #+#    #+#             */
/*   Updated: 2024/04/18 18:36:35 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*ptr;
	unsigned char	uc;
	size_t			len;
	size_t			i;

	if (!s)
		return (NULL);
	ptr = NULL;
	uc = (unsigned char)c;
	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (*s == uc)
		{
			ptr = (char *)(s);
			return (ptr);
		}
		s++;
		i++;
	}
	return (ptr);
}
