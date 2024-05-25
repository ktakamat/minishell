/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:43:02 by machi             #+#    #+#             */
/*   Updated: 2024/04/25 20:12:10 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*a;

	if (size != '\0' && (size * count) / size != count)
	{
		return (0);
	}
	a = malloc(size * count);
	if (a == NULL)
	{
		ft_exit();
	}
	ft_bzero(a, size * count);
	return (a);
}
