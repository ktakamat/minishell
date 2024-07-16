/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:48:09 by yususato          #+#    #+#             */
/*   Updated: 2024/07/15 17:06:06 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_token_kind
{
	TK_PIPE,
	TK_CMD,
	TK_SQUOTE,
	TK_DQUOTE,
	NOT_TK_QUOTE,
	TK_LESS,
	TK_DLESS,
	TK_GREAT,
	TK_DGREAT
}	t_token_kind;

typedef struct s_token
{
	t_token_kind		kind;
	struct s_token		*next;
	char				*str;
	bool				space_flag;
}	t_token;

typedef enum e_redirect_type
{
	UNKNOWN,
	QUOTE_HEREDOC,
	HEREDOC,
	IN_FILE,
	OUT_FILE,
	APPEND
}	t_redirect_type;

typedef struct s_file
{
	char				*file_name;
	t_redirect_type		type;
	struct s_file		*next;
}	t_file;

typedef struct s_parser
{
	char				**cmd;
	t_file				*file;
	struct s_parser		*next;
	struct s_parser		*prev;
}	t_parser;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_code
{
	RUN_ERROR,
	EXPORT_ERROR,
	UNSET_ERROR,
	NOT_FOUND_ERROR,
	FORK_ERROR,
	PARSE_ERROR,
	PARSE_ERROR_REDIRECT,
	PARSE_ERROR_REDIRECT_STR,
}	t_code;

bool		check_word(char	*line);
bool		is_pipe_redirect(t_token *lexer_tmp);
void		simple_counter(int *i, int *count);
bool		split_space(char **tmp, char *line);
t_token		*split_pipe(char **tmp, char *line);
t_token		*split_red(char **tmp, char *line);
t_token		*split_squote(char **tmp, char *line);
t_token		*split_dquote(char **tmp, char *line);
t_token		*split_word(char **tmp, char *line);
t_token		*lexer(char *line);
void		free_lexer(t_token *lexer_head);
t_parser	*parser(t_token	*lexer, t_env **env);
void		free_parser(t_parser *parser_head);
bool		is_redirect(t_token *lexer_tmp);
bool		is_quote(t_token_kind kind);
bool		cmd_init(t_token **lexer_tmp, t_parser **parser_tmp);
bool		cmd_add(t_token **lexer_tmp, t_parser **parser_tmp, char **tmp);
void		*parser_cmd(t_token **lexertmp, t_parser **parsertmp);
void		*parser_pipe(t_parser **parser_tmp, t_parser **parser);
t_parser	*parser_node_new(void);
bool		file_init(t_file **file, char *file_name, t_token_kind kind, \
												t_token_kind next_kind);
bool		file_add(t_file **file, char *file_name, t_token_kind kind, \
												t_token_kind next_kind);
void		*parser_redirect(t_token **lexer_tmp, t_parser **parser_tmp);
void		simple_insert(char *new, char c, int *count, int *i);
// bool		can_connect(t_token *next);
void		node_delete(t_token *tmp, t_token *tmp_next);
// void		token_check(t_token	*lexer);
void		*parser_check(t_token **lexer_tmp, t_parser **parser_tmp, \
												t_parser **parser);
t_token		*create_token(char *line, t_token_kind kind, bool flag);
int			question_add_len(int *i);
int			env_add_len(char *str, t_env **env, int *i);
void		str_insert(char	*new, char *str);
int			parser_env_add(char *str, t_env **env, char *new, int *i);
int			env_question_add(char *new, int *i, int *count);
char		*env_insert(char *str, t_env **env, int len);
t_token		*split_other(char **tmp, char *line);
bool		is_lexer_continue(char c);
bool		token_check_str(t_token	*lexer);
int			cmd_len(char *str, t_env **env);
bool		expand(t_token *lexer, t_env **env);
bool		expand_dquote(t_token *tmp, t_env **env);
bool		expand_cmd(t_token *tmp, t_env **env);
int			is_special_space(char *str);
void		env_process(char *str, char *new, t_env **env, int *count);
char		*head_env_check(char *line, int *i, int *j);
bool		env_process_heredoc(char *str, char *new, t_env **env, int *count);
bool		token_check_pipe_redirect(t_token *lexer);
bool		lexer_connect_check(t_token *lexer);
bool		lexer_null_check(t_token *lexer);

#endif