/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:13:53 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/13 23:10:48 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "./directory.h"
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>

# define EXIT_ERROR 2

typedef struct s_env
{
	char	*name;
	char	*content;
	char	*env_name;
	char	*env_val;
	char	**value;
	char	*key;
	int		num_value;
	bool	is_shell_var;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_args
{
	int		argc;
	char	**argv;
}	t_args;

int		execute_com(t_args	*args, t_env **env_head);
int		exe_exit(t_args *args);
int		exec_cd(t_directory *dir, char *path, t_env **head);
int		exe_pwd(t_args *args);
int		exec_echo(char **str, int m_words)
int		exe_env(t_env *head);
int		exe_ls(t_args *args);
int		exe_grep(t_args *args);
int		exe_cat(t_args *args);
int		exe_export(void);
int		exe_unset(void);
char	**minishell_split(char *s);
void	handle_sigint(int sig);
void	setup_signal_handlers(void);
t_env	*new_env_node(char *env_str);
t_env	*set_env_list(char **envp);
void	ft_free_args(t_args *args);
void print_env_list(t_env *env_list);
void	set_ready_env_vars(t_env **head, char *path);
t_env	*create_env_vars(char *envp[], char *path);

#endif