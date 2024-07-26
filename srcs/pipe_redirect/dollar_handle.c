/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:04:10 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/26 15:40:14 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*cpy_itoa(char *tmp, char *str, t_directory *dir)
{
	char	*num;
	char	*result;

	num = ft_itoa(dir->error.error_num);
	if (!num)
		exit(EXIT_FAILURE);
	result = malloc(ft_strlen(str) + ft_strlen(num) - 1);
	if (!result)
	{
		ft_free(num);
		exit(EXIT_FAILURE);
	}
	ft_memcpy(result, str, tmp - str);
	result[tmp - str] = '\0';
	ft_strcat(result, num);
	ft_strcat(result, tmp + 2);
	ft_free(num);
	return (result);
}

static char	*cpy_itoa_dd(char *tmp, char *str)
{
	char	*num;
	char	*result;

	num = ft_itoa(20870);
	if (!num)
		exit(EXIT_FAILURE);
	result = malloc(ft_strlen(str) + ft_strlen(num) - 1);
	if (!result)
	{
		ft_free(num);
		exit(EXIT_FAILURE);
	}
	ft_memcpy(result, str, tmp - str);
	result[tmp - str] = '\0';
	ft_strcat(result, num);
	ft_strcat(result, tmp + 2);
	ft_free(num);
	return (result);
}

char	*handle_question_mark(char *str, char *tmp, t_directory *dir)
{
	char	*processed;

	processed = cpy_itoa(tmp, str, dir);
	if (processed)
	{
		ft_free(str);
		str = processed;
	}
	else
		ft_free(str);
	return (str);
}

char	*handle_dollar_sign(char *str, char *tmp)
{
	char	*processed;

	processed = cpy_itoa_dd(tmp, str);
	if (processed)
	{
		ft_free(str);
		str = processed;
	}
	else
		ft_free(str);
	return (str);
}

char	*d_handle(char *str, t_directory *dir, t_env **head)
{
	char	*tmp;

	tmp = ft_strchr(str, '$');
	if (!tmp || !tmp[1])
		return (str);
	while (tmp && *tmp && *(tmp + 1))
	{
		if (!*(tmp + 1))
			break ;
		if (*(tmp + 1) == '?')
			str = handle_question_mark(str, tmp, dir);
		else if (*(tmp + 1) == '$')
			str = handle_dollar_sign(str, tmp);
		else
		{
			str = handle_default(str, head);
		}
		if (!str)
			break ;
		tmp = ft_strchr(str, '$');
	}
	return (str);
}
