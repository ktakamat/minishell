/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:54:02 by yususato          #+#    #+#             */
/*   Updated: 2023/06/01 13:06:48 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char const str, char charset)
{
	if (str == charset)
		return (1);
	return (0);
}

static int	len(char const *str, char charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*str)
	{
		if (*str == charset)
			i = 0;
		else if (!i)
		{
			i = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static char	*get(char const *str, char charset)
{
	char	*a;
	int		count;

	count = 0;
	while (str[count] && !check(str[count], charset))
		count++;
	a = (char *)malloc((sizeof(char) * (count + 1)));
	if (a == NULL)
		return (NULL);
	count = 0;
	while (*str && !(check(*str, charset)))
	{
		a[count] = *str;
		str++;
		count++;
	}
	a[count] = '\0';
	return (a);
}

static char	**checkfree(char **c, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(c[i]);
		i++;
	}
	free(c);
	return (NULL);
}

char	**ft_split(char const *str, char charset)
{
	size_t		i;
	char		**c;

	if (!str)
		return (NULL);
	i = 0;
	c = (char **)malloc(sizeof(char *) * (len(str, charset) + 1));
	if (c == NULL)
		return (NULL);
	while (*str)
	{
		if (check(*str, charset) == 0)
		{
			c[i] = get(str, charset);
			if (c[i] == NULL)
				return (checkfree(c, i));
			i++;
			while (*str && !check(*str, charset))
			str++;
		}
		else
			str++;
	}
	c[i] = NULL;
	return (c);
}
