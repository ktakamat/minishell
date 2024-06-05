/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:44:04 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/01 18:44:20 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dup(int fd)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd == -1)
		exit(EXIT_FAILURE);
	return (new_fd);
}
