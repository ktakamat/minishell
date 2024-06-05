/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:55:35 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/05 20:55:37 by ktakamat         ###   ########.fr       */
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
