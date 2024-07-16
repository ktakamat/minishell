/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:28:47 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/11 13:15:29 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*allocate_tenv(char *env_line);
static int		copy_kv(char *dest, char *ref);

t_env	*create_envnode(char *env_line)
{
	t_env	*env_node;
	int		index;

	index = 0;
	if (env_line == NULL)
		return (NULL);
	env_node = allocate_tenv(env_line);
	if (env_node == NULL)
		return (NULL);
	index += copy_kv(env_node->key, &env_line[index]);
	if (env_line[index] == '+')
		index += 2;
	else
		index += 1;
	copy_kv(env_node->value, &env_line[index]);
	return (env_node);
}

static int	copy_kv(char *dest, char *ref)
{
	int	index;

	index = 0;
	while (ref[index] != '\0' && ref[index] != '=' && ref[index] != '+')
	{
		dest[index] = ref[index];
		index++;
	}
	dest[index] = '\0';
	return (index);
}

static t_env	*allocate_tenv(char *env_line)
{
	int		key_value_len[2];
	t_env	*env_node;

	if (env_line == NULL)
		return (NULL);
	if (get_env_len(env_line, &key_value_len[0]) != 0)
		return (NULL);
	env_node = (t_env *)malloc(sizeof(t_env) * 1);
	if (env_node == NULL)
		return (NULL);
	env_node->key = (char *)malloc(sizeof(char) * (key_value_len[0] + 1));
	if (env_node->key == NULL)
	{
		free(env_node);
		return (NULL);
	}
	env_node->value = (char *)malloc(sizeof(char) * (key_value_len[1] + 1));
	if (env_node->value == NULL)
	{
		free(env_node);
		free(env_node->key);
		return (NULL);
	}
	env_node->next = NULL;
	return (env_node);
}

int	get_env_len(char *env, int *kv_lens)
{
	int	operand;

	if (env == NULL || kv_lens == NULL)
		return (-1);
	kv_lens[0] = 0;
	kv_lens[1] = 0;
	while (env[kv_lens[0]] != '=' && env[kv_lens[0]] != '+' \
									&& env[kv_lens[0]] != '\0')
		kv_lens[0]++;
	if (env[kv_lens[0]] == '\0' || \
			(env[kv_lens[0]] == '+' && env[kv_lens[0] + 1] != '='))
		return (1);
	else if (env[kv_lens[0]] == '+')
			operand = 2;
	else
		operand = 1;
	if (kv_lens[0] == 0)
		return (1);
	while (env[kv_lens[0] + kv_lens[1] + operand] != '\0')
		kv_lens[1]++;
	return (0);
}
