/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:31:11 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/14 20:31:18 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s1, const char *s2)
{
	size_t		count;

	count = 0;
	while (*s1)
	{
		if (ft_strchr(s2, *s1))
			count++;
		else
			break ;
		s1++;
	}
	return (count);
}
