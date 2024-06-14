/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:59:23 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/14 16:17:18 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*error_export(char *str)
{
	write(STDERR_FILENO, "minishell: export: `", 21);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "': not a valid identifier\n", 27);
	return (str);
}

char	*check_equal(char *cmds)
{
	int		i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i] == '=')
		{
			if (i == 0)
				return (error_export(cmds));
			return (cmds);
		}
		i++;
	}
	return (NULL);
}

char	*is_valid_name(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (error_export(name));
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_' && name[i] != '='
			&& name[i] != ':' && name[i] != '/'
			&& name[i] != '-' && name[i] != '.')
			return (error_export(name));
		i++;
	}
	return (NULL);
}

int	ft_declare(t_env *head)
{
	t_env		*current;
	int			i;

	current = head;
	while (current)
	{
		i = 0;
		printf("%s", "declare -x ");
		printf("%s=", current->key);
		printf("\"");
		while (i < current->num_value)
		{
			printf("%s", current->value[i]);
			if (i < current->num_value - 1)
				printf("%s", ":");
			i++;
		}
		printf("\"");
		printf("%s", "\n");
		current = current->next;
	}
	return (SUCCESS);
}

int	count_values(char **values)
{
	int	i;

	i = 0;
	while (values[i])
		i++;
	return (i);
}
