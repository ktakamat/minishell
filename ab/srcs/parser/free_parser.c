/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:16:45 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/15 14:13:53 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parser(t_parser *parser_head)
{
	t_parser	*current;
	t_parser	*tmp;
	t_file		*file;
	t_file		*file_tmp;

	current = parser_head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free_str_list(tmp->cmd);
		file = tmp->file;
		while (file != NULL)
		{
			if (tmp->file->type == HEREDOC | tmp->file->type == QUOTE_HEREDOC)
				unlink(tmp->file->file_name);
			free(file->file_name);
			file_tmp = file;
			file = file->next;
			free(file_tmp);
		}
		free(tmp);
	}
}
