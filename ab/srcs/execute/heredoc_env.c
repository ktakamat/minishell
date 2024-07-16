/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:19:41 by yususato          #+#    #+#             */
/*   Updated: 2024/07/11 13:15:32 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sdquote_space(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\'' && str[len] != '\"')
		len++;
	return (len);
}

int	heredoc_env_add(char *str, t_env **env, char *new, int *i)
{
	char	*env_value;
	int		len;
	char	*tmp;

	len = 0;
	len = is_special_space(str);
	*i += len + 1;
	tmp = ft_substr(str, 0, len);
	if (!tmp)
		return (-1);
	env_value = _getenv(*env, tmp);
	if (env_value == NULL)
		return (free(tmp), 0);
	len = ft_strlen(env_value);
	str_insert(new, env_value);
	free(env_value);
	free(tmp);
	return (len);
}

void	heredoc_count_init(int *i, int *tmp)
{
	*i = 0;
	*tmp = 0;
}

bool	env_process_heredoc(char *str, char *new, t_env **env, int *count)
{
	int		i;
	int		tmp;

	heredoc_count_init(&i, &tmp);
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '?')
				tmp = env_question_add(&new[*count], &i, count);
			else if (str[i + 1] == '\0' || str[i + 1] == ' '
				|| str[i + 1] == '$')
				simple_insert(new, str[i], count, &i);
			else
			{
				tmp = heredoc_env_add(&str[i + 1], env, &new[*count], &i);
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

char	*env_insert_heredoc(char *str, t_env **env, int len)
{
	int		count;
	char	*new;

	count = 0;
	new = (char *)ft_calloc(sizeof(char), len + 1);
	if (!new)
		return (NULL);
	if (env_process_heredoc(str, new, env, &count) == false)
		return (NULL);
	return (new);
}
