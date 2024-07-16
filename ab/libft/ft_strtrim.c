/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:48:51 by yususato          #+#    #+#             */
/*   Updated: 2023/05/26 19:49:21 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	start;
	size_t	end;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (start < end && ft_strchr(set, s1[start]))
	start++;
	while (end > start && ft_strrchr(set, s1[end - 1]))
	end--;
	new = ft_calloc(1, end - start + 1);
	if (new == NULL)
		return (NULL);
	while (start < end)
	{
		new[i] = s1[start];
		i++;
		start++;
	}
	return (new);
}
