/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:48:24 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/31 17:18:15 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*flatten_tenv(t_env *env)
{
	char	*line;
	int		lens[2];
	int		index;
	char	*result;

	index = 0;
	lens[0] = ft_strlen(env->key);
	result = join_value(env->value);
	lens[1] = ft_strlen(result);
	line = (char *)malloc(sizeof(char) * (lens[0] + lens[1] + 2));
	if (line == NULL)
		return (NULL);
	index += ft_strlcpy(&line[index], env->key, lens[0] + 1);
	line[index] = '=';
	index++;
	index += ft_strlcpy(&line[index], result, lens[1] + 1);
	free(result);
	return (line);
}

static int	get_tenv_len(t_env *env)
{
	t_env	*current;
	int		len;

	if (env == NULL)
		return (-1);
	current = env;
	len = 0;
	while (current != NULL)
	{
		current = current->next;
		len++;
	}
	return (len);
}

// char	**env_into_list(t_env *env_var)
// {
// 	char	**env_list;
// 	t_env	*current;
// 	int		env_len;
// 	int		index;

// 	if (env_var == NULL)
// 		return (NULL);
// 	current = env_var;
// 	index = 0;
// 	env_len = get_tenv_len(env_var);
// 	if (env_len < 0)
// 		return (NULL);
// 	env_list = (char **)malloc(sizeof(char *) * (env_len + 1));
// 	if (env_list == NULL)
// 		return (NULL);
// 	while (current != NULL && index < env_len)
// 	{
// 		env_list[index] = flatten_tenv(current);
// 		if (env_list[index] == NULL)
// 		{
// 			free_str_list(env_list);
// 			return (NULL);
// 		}
// 		current = current->next;
// 		index++;
// 	}
// 	env_list[index] = NULL;
// 	return (env_list);
// }

static char	**initialize_env_list(t_env *env_var, int *env_len)
{
	char	**env_list;

	*env_len = get_tenv_len(env_var);
	if (*env_len < 0)
		return (NULL);
	env_list = (char **)malloc(sizeof(char *) * (*env_len + 1));
	if (env_list == NULL)
		return (NULL);
	return (env_list);
}

static int	populate_env_list(t_env *env_var, char **env_list, int env_len)
{
	t_env	*current;
	int		index;

	current = env_var;
	index = 0;
	while (current != NULL && index < env_len)
	{
		env_list[index] = flatten_tenv(current);
		if (env_list[index] == NULL)
		{
			free_str_list(env_list);
			return (-1);
		}
		current = current->next;
		index++;
	}
	env_list[index] = NULL;
	return (0);
}

char	**env_into_list(t_env *env_var)
{
	char	**env_list;
	int		env_len;

	if (env_var == NULL)
		return (NULL);
	env_list = initialize_env_list(env_var, &env_len);
	if (env_list == NULL)
		return (NULL);
	if (populate_env_list(env_var, env_list, env_len) == -1)
		return (NULL);
	return (env_list);
}
