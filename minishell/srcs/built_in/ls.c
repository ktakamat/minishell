/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:59:57 by flaghata          #+#    #+#             */
/*   Updated: 2024/06/09 18:24:54 by flaghata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exe_ls(t_args *args)
{
    pid_t		pid;
    int         status;

    printf("ls\n");
    pid = ft_fork();
    if (pid == 0)
    {
        execve("/bin/ls", args->argv, NULL);
        exit(1);
    }
    else
    {
        waitpid(0, &status, 0);
    }
    return (1);
}
