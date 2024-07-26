/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:31:09 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/25 21:24:03 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	simple_counter(int *i, int *count)
{
	(*i)++;
	(*count)++;
}

int	is_equal_2(char *str, char *ref)
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

t_env	*find_node(t_env *env_head, char *key)
{
	t_env	*current;

	if (env_head == NULL || key == NULL)
		return (NULL);
	current = env_head;
	while (is_equal_2(current->key, key) != 1 && current->next != NULL)
		current = current->next;
	if (is_equal_2(current->key, key) == 1)
		return (current);
	else
		return (NULL);
}

char	*make_check(int *i)
{
	char	*new;
	char	*tmp;

	tmp = ft_itoa_2(*i);
	if (tmp == NULL)
		return (NULL);
	new = ft_strjoin(HEREDOC_FILE, tmp);
	if (new == NULL)
		return (free(tmp), NULL);
	free(tmp);
	while (!access(new, F_OK))
	{
		(*i)++;
		free(new);
		tmp = ft_itoa_2(*i);
		if (tmp == NULL)
			return (NULL);
		new = ft_strjoin(HEREDOC_FILE, tmp);
		if (new == NULL)
			return (free(tmp), NULL);
		free(tmp);
	}
	return (new);
}

char	*make_file(int *i)
{
	int		fd;
	char	*new;

	new = make_check(i);
	if (new == NULL)
		return (NULL);
	fd = open(new, O_CREAT, 0644);
	if (fd == -1)
		return (NULL);
	close(fd);
	return (new);
}
