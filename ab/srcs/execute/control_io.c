/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:49:40 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/10 14:51:59 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_io(int *original_io)
{
	if (original_io == NULL)
		return (-1);
	original_io[0] = dup(0);
	if (original_io[0] < 0)
		return (-1);
	original_io[1] = dup(1);
	if (original_io[1] < 0)
	{
		close(original_io[0]);
		perror("minishell");
		return (-1);
	}
	return (0);
}

int	get_back_io(int *original_io)
{
	if (dup2(original_io[WRITE], 1) < 0)
	{
		perror_set_flag("minishell: dup: ");
		close(original_io[WRITE]);
		close(original_io[READ]);
		return (-1);
	}
	if (dup2(original_io[READ], 0) < 0)
	{
		perror_set_flag("minishell: dup: ");
		close(original_io[WRITE]);
		close(original_io[READ]);
		return (-1);
	}
	close(original_io[WRITE]);
	close(original_io[READ]);
	return (0);
}
