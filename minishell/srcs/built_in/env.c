/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychiba <ychiba@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:18:43 by ychiba            #+#    #+#             */
/*   Updated: 2024/04/29 18:24:08 by ychiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exe_env(void)
{
	char	*pathvar;

	pathvar = getenv("PATH");
	printf("PATH=%s\n",pathvar);
	return (1);
}
