/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:43:53 by yususato          #+#    #+#             */
/*   Updated: 2023/05/29 19:42:54 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0' && i < n)
	{
		s1++;
		s2++;
		i++;
	}
	if (i == n)
		return (0);
	if (*s1 != *s2)
	{
		return ((unsigned char)*s1 - (unsigned char)*s2);
	}
	else
		return (0);
}
