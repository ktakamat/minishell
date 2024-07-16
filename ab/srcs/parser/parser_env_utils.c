/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:48:26 by yususato          #+#    #+#             */
/*   Updated: 2024/07/11 13:15:09 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_process(char *str, char *new, t_env **env, int *count)
{
	int		i;
	int		tmp;

	i = 0;
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
				tmp = parser_env_add(&str[i + 1], env, &new[*count], &i);
				*count += tmp;
			}
		}
		else
			simple_insert(new, str[i], count, &i);
	}
	new[*count] = '\0';
}

char	*env_insert(char *str, t_env **env, int len)
{
	int		count;
	char	*new;

	count = 0;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	env_process(str, new, env, &count);
	return (new);
}
