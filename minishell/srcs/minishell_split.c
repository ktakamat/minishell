/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychiba <ychiba@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:43:36 by ychiba            #+#    #+#             */
/*   Updated: 2024/04/29 15:22:27 by ychiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	word_count(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
			count++;
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (count);
}

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

void	init_split(t_split *sp, char *str)
{
	sp->i = 0;
	sp->j = 0;
	sp->k = 0;
	sp->count = word_count(str);
	sp->result = NULL;
}

char	**minishell_split(char *str)
{
	t_split	sp;

	init_split(&sp, str);
	sp.result = (char **)malloc(sizeof(char *) * (sp.count + 1));
	if (!sp.result)
		return (NULL);
	while (str[sp.i] && sp.k < sp.count)
	{
		while (str[sp.i] && ft_isspace(str[sp.i]))
			sp.i++;
		sp.j = sp.i;
		while (str[sp.i] && !ft_isspace(str[sp.i]))
			sp.i++;
		if (sp.j < sp.i)
		{
			sp.result[sp.k] = (char *)malloc(sizeof(char) * (sp.i - sp.j + 1));
			if (sp.result[sp.k] == NULL)
				return (NULL);
			ft_strncpy(sp.result[sp.k], &str[sp.j], sp.i - sp.j);
			sp.result[sp.k++][sp.i - sp.j] = '\0';
		}
	}
	sp.result[sp.k] = NULL;
	return (sp.result);
}
