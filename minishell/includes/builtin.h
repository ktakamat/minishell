/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaghata <flaghata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:13:53 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/09 18:25:49 by flaghata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <signal.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_env
{
	char	*name;
	char	*content;
	char	*env_name;
	char	*env_val;
	char	**value;
	char	*key;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_args
{
	int		argc;
	char	**argv;
}	t_args;

int		execute_com(t_args	*args);
int		exe_exit(t_args *args);
int		exe_chdir(t_args *args);
int		exe_pwd(t_args *args);
int		exe_echo(t_args args);
int		exe_env(void);
int		exe_ls(t_args *args);
int		exe_grep(t_args *args);
int		exe_export(void);
int		exe_unset(void);
char	**minishell_split(char *s);
void	handle_sigint(int sig);
void	setup_signal_handlers(void);
t_env	*new_env_node(char *env_str);
t_env	*set_env_list(char **envp);
void	ft_free_args(t_args *args);
int	main_loop(void);
void print_env_list(t_env *env_list);


#endif