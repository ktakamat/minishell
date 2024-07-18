/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:08:32 by ktakamat          #+#    #+#             */
/*   Updated: 2023/05/23 18:34:56 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (*(needle) == '\0')
	{
		return ((char *)haystack);
	}
	while (len-- > 0)
	{
		i = 0;
		while (haystack[i] == needle[i])
		{
			if (needle[i + 1] == '\0')
				return ((char *)haystack);
			if (i >= len)
				return (NULL);
			i++;
		}
		if (haystack[i] == '\0')
			return (NULL);
		haystack++;
	}
	return (NULL);
}
