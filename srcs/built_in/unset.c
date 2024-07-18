/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:44:53 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/14 17:49:40 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_var(t_env *var)
{
	int	i;

	i = 0;
	ft_free(var->key);
	while (i < var->num_value)
	{
		ft_free(var->value[i]);
		i++;
	}
	ft_free(var->value);
	ft_free(var);
}

static int	helper_unset(t_env **head, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	if (key[0] == '_')
		return (SUCCESS);
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free_var(current);
			return (SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (FAILURE);
}

static char	*error_unset(char *str)
{
	write(STDERR_FILENO, "minishell: unset: `", 20);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "': not a valid identifier\n", 27);
	return (ft_strchr(str, '='));
}

static char	*valid_nam_unset(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (error_unset(key));
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (error_unset(key));
		i++;
	}
	return (NULL);
}

int	exec_unset(t_env **head, char **keys, int *flags)
{
	int		status;
	int		i;

	status = SUCCESS;
	i = 1;
	while (keys[i])
	{
		if (flags[i] == 0 && valid_nam_unset(keys[i]))
			status = FAILURE;
		helper_unset(head, keys[i]);
		i++;
	}
	return (status);
}
