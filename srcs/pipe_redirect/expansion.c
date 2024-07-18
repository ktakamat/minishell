/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:22:59 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/06 17:22:17 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	temp_result(t_expand *exp, char **result)
{
	exp->temp = *result;
	*result = ft_strjoin(*result, exp->value);
	ft_free(exp->temp);
	if (!result)
	{
		exit(EXIT_FAILURE);
	}
}

static void	handle_values(t_expand *exp, char **values, char **result)
{
	int	i;

	if (values)
	{
		i = 0;
		while (values[i])
		{
			exp->value = values[i];
			temp_result(exp, result);
			if (values[i + 1])
			{
				exp->temp = *result;
				*result = ft_strjoin(*result, ":");
				ft_free(exp->temp);
				if (!result)
					exit(EXIT_FAILURE);
			}
			i++;
		}
	}
}

static void	handle_dollar_sign_1(t_expand *exp, char *varname,
	char **result, t_env **head)
{
	char	**values;

	exp->flag = 1;
	exp->end = exp->start + 1;
	while (ft_isalnum(*exp->end) || *exp->end == '_')
		exp->end++;
	ft_strlcpy(varname, exp->start + 1, exp->end - exp->start);
	exp->start = exp->end;
	values = search(head, varname);
	handle_values(exp, values, result);
}

static void	handle_no_dollar_sign(t_expand *exp, char **result)
{
	char	*buffer;

	buffer = (char *)malloc(2 * sizeof(char));
	if (!buffer)
		exit(EXIT_FAILURE);
	buffer[0] = *exp->start;
	buffer[1] = '\0';
	exp->temp = *result;
	*result = ft_strjoin(*result, buffer);
	if (!result)
		exit(EXIT_FAILURE);
	ft_free(exp->temp);
	ft_free(buffer);
	exp->start++;
}

char	*expand_and_replace(char *input, t_env **head)
{
	char		varname[MAX_BUFFER_SIZE];
	char		*result;
	t_expand	exp;

	exp.flag = 0;
	result = (char *)ft_calloc(MAX_BUFFER_SIZE, sizeof(char));
	if (!result)
		exit(EXIT_FAILURE);
	exp.start = input;
	while (*exp.start != '\0')
	{
		if (*exp.start == '$')
		{
			if (exp.flag == 1)
			{
				append_expanded(&exp, &result);
				break ;
			}
			handle_dollar_sign_1(&exp, varname, &result, head);
		}
		else
			handle_no_dollar_sign(&exp, &result);
	}
	return (result);
}
