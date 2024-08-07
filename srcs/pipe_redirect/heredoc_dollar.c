/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:01:03 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/29 18:43:40 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	special_space(char *str)
{
	int	len;

	len = 0;
	while (str[len] && ft_isalnum(str[len]))
		len++;
	return (len);
}

int	question_len(int *i)
{
	int		len;
	char	*tmp;

	tmp = ft_itoa_2(*i);
	if (tmp == NULL)
		return (-1);
	len = ft_strlen(tmp);
	*i += 2;
	free(tmp);
	return (len);
}

char	*join_value(char **value)
{
	int		i;
	int		len;
	char	*result;

	if (value == NULL || value[0] == NULL)
		return (NULL);
	len = 0;
	i = 0;
	while (value[i] != NULL)
		len += ft_strlen(value[i++]) + 1;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	i = 0;
	while (value[i] != NULL)
	{
		if (i > 0)
			ft_strcat(result, ":");
		ft_strcat(result, value[i]);
		i++;
	}
	return (result);
}

char	*get_env(t_env *env_var, char *key)
{
	t_env	*node;
	char	*line;

	if (env_var == NULL || key == NULL)
		return (NULL);
	node = find_node(env_var, key);
	line = join_value(node->value);
	if (line == NULL)
		return (NULL);
	return (line);
}

int	env_len(char *str, t_env **env_var, int *i)
{
	char	*head;
	int		len;
	char	*tmp;

	len = 0;
	(*i)++;
	if (!ft_isalnum(str[0]))
		return (1);
	len = special_space(str);
	*i += len;
	tmp = ft_substr(str, 0, len);
	if (!tmp)
		return (-1);
	head = get_env(*env_var, tmp);
	if (!head)
		return (free(tmp), 0);
	free(tmp);
	len = ft_strlen(head);
	free(head);
	return (len);
}
