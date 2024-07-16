/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:59:22 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/16 14:55:54 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_token *lexer_head)
{
	t_token	*current;
	t_token	*tmp;

	current = lexer_head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		if (tmp->str != NULL)
			free(tmp->str);
		free(tmp);
	}
}
