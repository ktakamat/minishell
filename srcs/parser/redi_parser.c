/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:11:14 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/29 18:38:53 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_redirect	*create_redirect(void)
{
	t_redirect	*redi;

	redi = malloc(sizeof(t_redirect));
	if (!redi)
		exit(EXIT_FAILURE);
	redi->type = 0;
	redi->fd = -1;
	redi->fd_file = -1;
	redi->fd_backup = -1;
	redi->file_name = NULL;
	redi->next = NULL;
	return (redi);
}

static t_redirect_type	redirect_type(t_token **token)
{
	if ((*token)->kind == TK_LESS)
		return (INPUT_REDI);
	else if ((*token)->kind == TK_GREAT)
		return (OUTPUT_REDI);
	else if ((*token)->kind == TK_DGREAT)
		return (APPEND_OUTPUT_REDI);
	else
		return (HEREDOC_REDI);
}

// int	set_redirect(t_parser *parser, t_token **token, t_env **env_var)
// {
// 	t_redirect	*redi;
// 	t_redirect	*new;

// 	if ((*token)->next == NULL)
// 		return (FAILURE);
// 	new = create_redirect();
// 	new->type = redirect_type(token);
// 	new->file_name = ft_strdup((*token)->next->str);
// 	if ((*token)->kind == TK_LESS)
// 		new->fd = STDIN_FILENO;
// 	else if ((*token)->kind == TK_GREAT)
// 		new->fd = STDOUT_FILENO;
// 	else if ((*token)->kind == TK_DGREAT)
// 		new->fd = STDOUT_FILENO;
// 	else if ((*token)->kind == TK_DLESS)
// 	{
// 		new->fd = STDIN_FILENO;
// 		here_doc(new, env_var);
// 	}
// 	if (parser->redirect == NULL)
// 		parser->redirect = new;
// 	else
// 	{
// 		redi = parser->redirect;
// 		while (redi->next != NULL)
// 			redi = redi->next;
// 		redi->next = new;
// 	}
// 	(*token) = (*token)->next->next;
// 	return (SUCCESS);
// }

int	set_redirect(t_parser *parser, t_token **token, t_env **env_var)
{
	t_redirect	*redi;
	t_redirect	*new;

	if ((*token)->next == NULL)
		return (FAILURE);
	new = create_redirect();
	new->type = redirect_type(token);
	new->file_name = ft_strdup((*token)->next->str);
	if ((*token)->kind == TK_LESS || (*token)->kind == TK_GREAT
		|| (*token)->kind == TK_DGREAT || (*token)->kind == TK_DLESS)
		new->fd = STDIN_FILENO;
	if ((*token)->kind == TK_DLESS)
		here_doc(new, env_var);
	if (parser->redirect == NULL)
		parser->redirect = new;
	else
	{
		redi = parser->redirect;
		while (redi->next != NULL)
			redi = redi->next;
		redi->next = new;
	}
	(*token) = (*token)->next->next;
	return (SUCCESS);
}

void	destroy_redirect(t_redirect *redi)
{
	t_redirect	*tmp;

	while (redi != NULL)
	{
		tmp = redi->next;
		if (redi->type == HEREDOC_REDI)
			unlink(redi->file_name);
		if (redi->file_name != NULL)
			ft_free(redi->file_name);
		ft_free(redi);
		redi = tmp;
	}
}
