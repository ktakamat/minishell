/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:41:35 by ktakamat          #+#    #+#             */
/*   Updated: 2024/05/02 16:40:58 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_connectable_quote(t_token *token_head)
{
    if (token_head->kind == TK_SQUOTE || token_head->kind == TK_DQUOTE)
        return true;
    return false;
}

bool is_parser_quote(t_token_kind kind)
{
    if (kind == TK_SQUOTE || kind == TK_DQUOTE)
        return true;
    return false;
}

bool can_connect_start(t_token *token_head)
{
    if (token_head->kind == TK_SQUOTE || token_head->kind == TK_DQUOTE
        || token_head->kind == TK_CMD)
        return true;
    return false;
}

bool is_redirect(t_token *token_head)
{
    if (token_head->kind == TK_GREAT || token_head->kind == TK_DGREAT
        || token_head->kind == TK_LESS || token_head->kind == TK_DLESS)
        return true;
    return false;
}

bool can_connect(t_token *token_head)
{
    if (token_head->kind == TK_SQUOTE || token_head->kind == TK_DQUOTE
        || token_head->kind == TK_CMD)
        return true;
    return false;
}

void evolve_token(t_token *token_head)
{
    t_token *tmp;
    char *tmp_str;

    tmp = token_head->next;
    while (tmp != token_head && tmp->next != token_head)
    {
        if (can_connect_start(tmp) == true && can_connect(tmp->next) == true)
        {
            tmp_str = tmp->str;
            tmp->str = ft_strjoin(tmp_str, tmp->next->str);
            if (tmp->str == NULL)
            {
                ft_puterr_malloc();
                return;
            }
            free(tmp_str);
            token_node_delete(tmp->next);
        }
        else
            tmp = tmp->next;
    }
}

void	token_node_delete(t_token *target)
{
	t_token	*target_prev;
	t_token	*target_next;

	if (target == NULL)
		return ;
	target_next = target->next;
	target_prev = target->prev;
	target_prev->next = target_next;
	target_next->prev = target_prev;
	free(target->str);
	target->str = NULL;
	free(target);
	target = NULL;
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_puterr(char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
}

void	ft_puterr_malloc(void)
{
	ft_puterr("\033[31m malloc error\n \033[0m");
	exit(1);
}