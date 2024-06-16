/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:30:55 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/14 20:31:07 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s1r, const char *s2r)
{
	const char	*s1 = s1r;
	const char	*s2;

	while (*s1)
	{
		s2 = s2r;
		while (*s2)
		{
			if (*s1 == *s2++)
				return (s1 - s1r);
		}
		s1++;
	}
	return (s1 - s1r);
}
