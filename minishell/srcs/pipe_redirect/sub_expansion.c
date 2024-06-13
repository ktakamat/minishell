/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:18:55 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/03 15:19:45 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append_expanded(t_expand *exp, char **result)
{
	exp->temp = *result;
	*result = ft_strjoin(*result, exp->start);
	if (!*result)
		exit(EXIT_FAILURE);
	ft_free(exp->temp);
}

int	get_var_length(const char *str)
{
	int	len;

	len = 1;
	while (str[len] != '\0' && str[len] != '\"'
		&& str[len] != '\'' && !ft_isspace(str[len]))
		len++;
	return (len);
}

char	*expansion(char *str, t_directory *dir, t_env **env_var)
{
	if (is_quoted(str))
		str = q_handle(str, dir, env_var);
	else
		str = d_handle(str, dir, env_var);
	return (str);
}
