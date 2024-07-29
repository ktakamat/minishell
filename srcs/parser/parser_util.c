/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:34:04 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/30 07:15:51 by flaghata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser	*node_new(void)
{
	t_parser	*node;

	node = malloc(sizeof(t_parser));
	if (node == NULL)
		exit(EXIT_FAILURE);
	node->type = CMD;
	node->cmd = NULL;
	node->redirect = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_parser	*destroy_parser(t_parser *parser)
{
	size_t	i;

	if (parser == NULL)
		return (NULL);
	if (parser->left)
		destroy_parser(parser->left);
	if (parser->right)
		destroy_parser(parser->right);
	if (parser->cmd)
	{
		i = 0;
		while (parser->cmd[i])
		{
			ft_free(parser->cmd[i]);
			i++;
		}
		ft_free(parser->cmd);
	}
	if (parser->redirect)
		destroy_redirect(parser->redirect);
	ft_free(parser);
	return (NULL);
}
