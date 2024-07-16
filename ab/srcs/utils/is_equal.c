/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_equal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:17:53 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/19 13:19:27 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_equal(char *str, char *ref)
{
	int	iter;

	iter = 0;
	if (str == NULL || ref == NULL)
		return (-1);
	while (str[iter] && ref[iter])
	{
		if (str[iter] != ref[iter])
			return (0);
		iter++;
	}
	if (str[iter] == '\0' && ref[iter] == '\0')
		return (1);
	else
		return (0);
}
