/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:17:59 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/25 15:53:13 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_count_zero(int *i, int *tmp)
{
	*i = 0;
	*tmp = 0;
}

int	heredoc_add(char *str, t_env **env_var, char *new, int *i)
{
	char	*env_value;
	int		len;
	char	*tmp;

	len = 0;
	len = special_space(str);
	*i += len + 1;
	tmp = ft_substr(str, 0, len);
	if (!tmp)
		return (-1);
	env_value = get_env(*env_var, tmp);
	if (env_value == NULL)
		return (free(tmp), 0);
	len = ft_strlen(env_value);
	str_insert(new, env_value);
	free(env_value);
	free(tmp);
	return (len);
}

bool	process_heredoc(char *str, char *new, t_env **env_var, int *count)
{
	int	i;
	int	tmp;

	heredoc_count_zero(&i, &tmp);
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '?')
				tmp = question_add(&new[*count], &i, count);
			else if (str[i + 1] == '\0' || str[i + 1] == ' '
				|| str[i + 1] == '$')
				simple_insert(new, str[i], count, &i);
			else
			{
				tmp = heredoc_add(&str[i + 1], env_var, &new[*count], &i);
				*count += tmp;
			}
		}
		else
			simple_insert(new, str[i], count, &i);
		if (tmp == -1)
			return (false);
	}
	return (true);
}

char	*insert_heredoc(char *str, t_env **env_var, int len)
{
	int		count;
	char	*new;

	count = 0;
	new = (char *)ft_calloc(sizeof(char), len + 1);
	if (!new)
		return (NULL);
	if (process_heredoc(str, new, env_var, &count) == false)
		return (NULL);
	return (new);
}
