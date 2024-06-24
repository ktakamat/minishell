/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:45:55 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/24 15:20:12 by ktakamat         ###   ########.fr       */
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
# define NODE_PIPE 1

typedef enum e_token_kind
{
	TK_PIPE,
	TK_CMD,
	TK_SQUOTE,
	TK_DQUOTE,
	TK_LESS,
	TK_DLESS,
	TK_GREAT,
	TK_DGREAT
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

t_token		*lexer(char *line);
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
void		parse_tokens(t_token *tokens);
char		*get_pass(char	*line);
int			token_count(t_token *token);
char		**token_list(t_token *token);
void		use_history(const char *line);
char		**parse_pipeline(char *line);
t_parser	*parser(t_token *tokens);
void		check_pipe(t_parser *parser, t_args *args);
bool		is_quoted(char *cmd);
void		process_dollar(t_parse_context *ctx);
void		process_normal_character(t_parse_context *ctx);
void		state_normal_plus(t_parse_context *ctx, t_parse_state *state);
char		*expansion(char *str, t_directory *dir, t_env **env_var);
char		*d_handle(char *str, t_directory *dir, t_env **head);
char		*q_handle(char *str, t_directory *dir, t_env **env_var);
bool		rect(char c);
int			set_redirect(t_parser *parser, t_token **token);
char		*expand_and_replace(char *input, t_env **head);
int			get_var_length(const char *str);
char		*handle_default(char *str, t_env **head);
char		**search(t_env **head, char *key);
void		append_expanded(t_expand *exp, char **result);
void		exec_command(t_parser *parser, t_directory *dir, t_env **env_var);
void		execution(t_parser *parser, t_directory *dir, t_env **env_var);
int			exec_redirect(t_redirect *redi, t_directory *dir, t_env **env_var);
void		pipe_line(t_parser *parser, t_directory *dir, t_env **env_var);
void		restore_fd(t_redirect *redi);
bool		is_redirect(char c);
void		setup_signals(void);
int			validate_cmds(char **cmds, t_directory *dir, t_env **env_var);
t_parser	*node_new(void);
t_parser	*handle_pipe(t_token **token, t_parser *parser);
t_token		*create_token_from_line(char **line, int *i, int *j);
bool		put_data(t_parser *parser, t_token **token);
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

#endif
