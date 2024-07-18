/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:13:53 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/18 20:42:32 by ktakamat         ###   ########.fr       */
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
	char			*name;
	char			*content;
	char			*env_name;
	char			*env_val;
	char			**value;
	char			*key;
	int				num_value;
	bool			is_shell_var;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_args
{
	int		argc;
	char	**argv;
}	t_args;

int		exec_exit(char **args);
void	exec_builtin(char **cmds, t_directory *dir, t_env **env_vars);
int		exec_cd(t_directory *dir, char *path, t_env **head);
int		exec_pwd(t_directory *dir);
int		exec_echo(char **str, int m_words);
int		exec_env(t_env *head);
int		exe_export(t_env **head, char **cmds, int *flags);
int		exec_unset(t_env **head, char **keys, int *flags);
char	**minishell_split(char *s);
void	handle_sigint(int sig);
void	setup_signal_handlers(void);
t_env	*new_env_node(char *env_str);
t_env	*set_env_list(char **envp);
void	ft_free_args(t_args *args);
void	print_env_list(t_env *env_list);
void	set_ready_env_vars(t_env **head, char *path);
t_env	*create_env_vars(char *envp[], char *path);
char	**null_free(char *str);
int		count_values(char **values);
int		exist_value(t_env *exist_node, char *values,
			char **split_result, char *key);
char	*is_valid_name(char *name);
bool	is_builtins(char *command);
char	*check_equal(char *cmds);
int		ft_declare(t_env *head);
void	execute_from_path(char **cmds, t_directory *dir, t_env **env_vars);
bool	check_file(char *path, t_directory *dir);
bool	check_fd_dir(char *path, t_directory *dir);
int		parsed_command_exec(char *command, char **cmds, t_env **env_vars);
void	combine_strings(char *s1, char *s2, char *s3, char *s4);
int		command_path_exec(char *command_path, char **cmds);
int		str_error(char *str);
void	print_error(const char *msg, const char *path);
int		validate_cmds(char **cmds, t_directory *dir, t_env **env_var);
void	clean_cmds(char **cmds, t_directory *dir,
			t_env **env_var);
char	*error_export(char *str);

#endif
