/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_waitpid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:51:50 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/03 17:52:29 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_waitpid(pid_t pid, int *status, int options)
{
	if (waitpid(pid, status, options) == -1)
		exit(EXIT_FAILURE);
}
