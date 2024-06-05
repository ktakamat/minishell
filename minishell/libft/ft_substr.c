/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:22:35 by machi             #+#    #+#             */
/*   Updated: 2024/04/25 20:14:22 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*a;
	size_t			sum;

	if (!s)
		return (NULL);
	sum = ft_strlen(s);
	if (sum - start < len)
		len = sum - start;
	if (start >= sum || len == 0)
		return (ft_strdup(""));
	a = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	if (a == NULL)
		ft_exit();
	while (i < len)
	{
		a[i] = s[start + i];
		i++;
	}
	a[i] = '\0';
	return (a);
}
