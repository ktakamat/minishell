/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:45:55 by ktakamat          #+#    #+#             */
/*   Updated: 2024/07/29 18:06:21 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "./builtin.h"
# include "./parser.h"
# include "./redirect.h"
# include "./directory.h"
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h> 
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h> 

# define MAX_SIZE 100
# define MAX_HISTORY_SIZE 100
# define PIPE_READ	0
# define PIPE_WRITE	1

volatile sig_atomic_t	g_interrupted;

typedef enum e_token_kind
{
	TK_PIPE,
	TK_CMD,
	TK_SQUOTE,
	TK_DQUOTE,
	TK_LESS,
	TK_DLESS,
	TK_GREAT,
	TK_DGREAT,
	TK_GENERAL
}	t_token_kind;

typedef struct s_token
{
	t_token_kind	kind;
	struct s_token	*next;
	char			*str;
	char			*line;
}	t_token;

typedef struct s_split
{
	int		count;
	int		i;
	int		j;
	int		k;
	char	**result;
}	t_split;

t_token		*lexer(char *line, int *i, int *j);
t_token		*create_word_token(char **tmp, char *line);
t_token		*create_dquote_token(char **tmp, char *line);
t_token		*create_squote_token(char **tmp, char *line);
t_token		*create_red_token(char **tmp, char *line);
t_token		*create_pipe_token(char **tmp, char *line);
bool		skip_space(char **tmp, char *line);
t_token		*create_token(char *line, t_token_kind kind);
bool		check_word(char*line);
void		remove_squote(t_token *token);
void		expand(t_token *token);
void		ft_error(void);
void		remove_dquote(t_token *token);
char		**token_list(t_token *token);
void		s(t_token *tokens);
char		*get_pass(char	*line);
int			token_count(t_token *token);
char		**token_list(t_token *token);
void		use_history(const char *line);
char		**parse_pipeline(char *line);
t_parser	*parser(t_token *tokens, t_directory *dir, int *error,
				t_env **env_var);
void		check_pipe(t_parser *parser, t_args *args);
bool		is_quoted(char *cmd);
void		process_dollar(t_parse_context *ctx);
void		process_normal_character(t_parse_context *ctx);
void		state_normal_plus(t_parse_context *ctx, t_parse_state *state);
char		*expansion(char *str, t_directory *dir, t_env **env_var);
char		*d_handle(char *str, t_directory *dir, t_env **head);
char		*q_handle(char *str, t_directory *dir, t_env **env_var);
bool		rect(char c);
int			set_redirect(t_parser *parser, t_token **token, t_env **env_var);
char		*expand_and_replace(char *input, t_env **head);
int			get_var_length(const char *str);
char		*handle_default(char *str, t_env **head);
char		**search(t_env **head, char *key);
void		append_expanded(t_expand *exp, char **result);
void		exec_command(t_parser *parser, t_directory *dir, t_env **env_var);
void		execution(t_parser *parser, t_directory *dir, t_env **env_var);
int			exec_redirect(t_parser *node, t_redirect *redi, t_directory *dir,
				t_env **env_var);
void		pipe_line(t_parser *parser, t_directory *dir, t_env **env_var);
bool		is_redirect(char c);
void		setup_signals(void);
int			validate_cmds(char **cmds, t_directory *dir, t_env **env_var);
t_parser	*node_new(void);
t_parser	*handle_pipe(t_token **token, t_parser *parser, t_env **env_var);
t_token		*create_token_from_line(char **line, int *i, int *j);
t_token		*create_dless_token(char **tmp, char *line);
t_token		*create_less_token(char **tmp, char *line);
t_token		*create_dgreat_token(char **tmp, char *line);
t_token		*create_great_token(char **tmp, char *line);
size_t		data_size(t_token *token);
bool		allocate_command_memory(t_parser *parser, t_token *token);
bool		process_tokens(t_parser *parser, t_token **token);
void		handle_sigint(int signal);
void		handle_exec(int signal);
void		exec_signals(void);
void		exe_signals(t_parser *node, t_directory *dir,
				t_env **env_vars, int *error);
void		setup_signals(void);
void		handle_sigint(int signal);
void		token_clear(t_token *token);
void		destroy_redirect(t_redirect *redi);
t_parser	*destroy_parser(t_parser *node);
int			main_loop(char *envp[], int *error);
char		*handle_input(void);
void		cleanup(char *line, t_parser *node, t_args *args);
int			exec_pre(t_redirect *redi, t_directory *dir, t_env **env_var);
bool		soro_redirect(char *line, int *error);
bool		here_doc(t_redirect *redi, t_env **env_var);
int			is_equal(char *str, char *ref);
char		*expand_heredoc(char *line, t_env **env_var);
bool		write_heredoc(char *line, t_env **env_var,
				int fd);
bool		read_here_doc(t_redirect *redi, t_env **env_var, int fd);
bool		file_name_change(t_redirect *redi, char *new_file);
char		*make_check(int *i);
char		*make_file(int *i);
void		simple_counter(int *i, int *count);
int			question_add(char *new, int *i, int *count);
void		simple_insert(char *new, char c, int *count, int *i);
void		str_insert(char	*new, char *str);
int			special_space(char *str);
char		*get_env(t_env *env_var, char *key);
char		*insert_heredoc(char *str, t_env **env_var, int len);
int			cmd_len(char *str, t_env **env_var);
void		signal_heredoc(void);
t_env		*find_node(t_env *env_head, char *key);
void		rm_heredoc_file(void);
void		syntax_error_null(t_token *token);
void		syntax_error_pipe(void);
int			syntax_error_code(t_directory *dir, int *error);
void		rm_heredoc_file(void);
void		perror_set_flag(char *insert, t_directory *dir);
int			redirect_in_out(t_redirect *head, t_directory *dir);
int			save_in_out(int *in_out);
int			get_back_in_out(int *std_in_out, t_directory *dir);
int			dir_error_num(t_directory *dir, int *error);
int			exit_command(int *error, t_directory *dir, t_parser	*node);
char		*remove_dollar_to_quote(const char *input);
// void		is_pipe_tokens(t_token *tokens, int *error, t_directory *dir);
// t_parser	*exit_parser_fail_put_data(int *error, t_directory *dir,
// 				t_token *tmp, t_parser *node);
// t_parser	*exit_parser_invalid_pipe_cmd(int *error, t_directory *dir,
// 				t_parser *node);
// void		is_redirect_token(t_token *tokens, int *error, t_directory *dir);
// void		is_valid_tokens(t_token *tokens, int *error, t_directory *dir);

#endif
