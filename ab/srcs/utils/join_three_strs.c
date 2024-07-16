/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_three_strs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:44:36 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/11 11:44:56 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_three_strs(char *s1, char *s2, char *s3)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(s1, s2);
	tmp2 = ft_strjoin(tmp1, s3);
	free(tmp1);
	return (tmp2);
}
