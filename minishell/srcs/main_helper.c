/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:10:15 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/17 17:05:47 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*construct_path(char *str, char *line)
{
	char	path[PATH_MAX];
	char	*end;

	bzero(path, PATH_MAX);
	end = ft_strchr(str, ':');
	if (end)
		ft_strncpy(path, str, end - str);
	else
		ft_strlcpy(path, str, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, line, PATH_MAX);
	if (access(path, X_OK) == 0)
		return (ft_strdup(path));
	return (NULL);
}

char	*get_pass(char *line)
{
	char	*str;
	char	*path;

	str = getenv("PATH");
	while (*str)
	{
		path = construct_path(str, line);
		if (path != NULL)
			return (path);
		str = ft_strchr(str, ':');
		if (str == NULL)
			break ;
		str++;
	}
	return (NULL);
}

// char	*get_pass(char *line)
// {
// 	char	path[PATH_MAX];
// 	char	*str;
// 	char	*end;
// 	char	*copy;

// 	str = getenv("PATH");
// 	while (*str)
// 	{
// 		bzero(path, PATH_MAX);
// 		end = ft_strchr(str, ':');
// 		if (end)
// 			ft_strncpy(path, str, end - str);
// 		else
// 			ft_strlcpy(path, str, PATH_MAX);
// 		ft_strlcat(path, "/", PATH_MAX);
// 		ft_strlcat(path, line, PATH_MAX);
// 		if (access(path, X_OK) == 0)
// 		{
// 			copy = ft_strdup(path);
// 			if (copy == NULL)
// 				return (NULL);
// 			return (copy);
// 		}
// 		if (end == NULL)
// 			return (NULL);
// 		str = end + 1;
// 	}
// 	return (NULL);
// }

int	token_count(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**token_list(t_token *token)
{
	int		i;
	char	**args;

	i = 0;
	i = token_count(token);
	args = calloc(i + 1, sizeof(char *));
	if (!args)
		ft_error();
	i = 0;
	while (token != NULL)
	{
		args[i] = ft_strdup(token->str);
		i++;
		token = token->next;
	}
	return (args);
}

void	use_history(const char *line)
{
	static int	history_index = 0;

	if (line[0] != '\0')
	{
		add_history(line);
		history_index++;
	}
	if (history_index >= MAX_HISTORY_SIZE)
	{
		remove_history(0);
		history_index--;
	}
}
