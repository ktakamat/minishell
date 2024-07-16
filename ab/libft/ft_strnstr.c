/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:51:45 by yususato          #+#    #+#             */
/*   Updated: 2023/05/29 21:55:42 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	search(const char *str, const char *to_find, size_t len, size_t i)
{
	size_t	a;

	a = 0;
	while (to_find[a] != '\0' && i < len)
	{
		if (to_find[a] != str[a])
			return (0);
		a++;
		i++;
	}
	if (a != ft_strlen(to_find))
		return (0);
	return (1);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;

	if (to_find[0] == '\0')
		return ((char *)(str));
	if (len == 0)
		return (0);
	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == *to_find)
		{
			if (search(&str[i], to_find, len, i))
				return ((char *)(&str[i]));
		}
		i++;
	}
	return (NULL);
}
