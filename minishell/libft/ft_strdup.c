/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:28:01 by ktakamat          #+#    #+#             */
/*   Updated: 2024/04/25 20:13:48 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		ft_exit();
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
