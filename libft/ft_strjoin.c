/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:55:35 by machi             #+#    #+#             */
/*   Updated: 2024/07/06 17:20:05 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*result;
// 	size_t	len_s1;
// 	size_t	len_s2;
// 	size_t	i;

// 	if (!s1)
// 		s1 = ft_strdup("");
// 	len_s1 = ft_strlen(s1);
// 	len_s2 = ft_strlen(s2);
// 	result = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
// 	if (!result)
// 		ft_exit();
// 	i = -1;
// 	while (s1[++i] != '\0')
// 		result[i] = s1[i];
// 	i = -1;
// 	while (s2[++i] != '\0')
// 	{
// 		result[len_s1] = s2[i];
// 		len_s1++;
// 	}
// 	result[len_s1] = '\0';
// 	free((void *)s1);
// 	return (result);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ans;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ans = (char *)malloc(sizeof(char) * len);
	if (!ans)
		return (NULL);
	*ans = '\0';
	ft_strlcat(ans, s1, ft_strlen(s1) + 1);
	ft_strlcat(ans, s2, len);
	return (ans);
}
