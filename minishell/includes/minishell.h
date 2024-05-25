/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:17:06 by ychiba            #+#    #+#             */
/*   Updated: 2024/05/24 22:21:50 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./builtin.h"
# include "./parser.h"
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h> 

# define MAX_SIZE 100
#define MAX_HISTORY_SIZE 100
#define NODE_PIPE 1

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
	t_token_kind kind;
	struct s_token	*next;
	// struct s_token	*prev;
	char	*str;
	char		*line;
	// size_t		n_pipe;
}	t_token;

typedef struct s_split
{
	int		count;
	int		i;
	int		j;
	int		k;
	char	**result;
}	t_split;


t_token	*lexer(char *line);
t_token	*split_word(char **tmp, char *line);
t_token	*split_dquote(char **tmp, char *line);
t_token	*split_squote(char **tmp, char *line);
t_token	*split_red(char **tmp, char *line);
t_token	*split_pipe(char **tmp, char *line);
bool	split_space(char **tmp, char *line);
t_token	*create_token(char *line, t_token_kind kind);
bool	check_word(char*line);
void	remove_squote(t_token *token);
void	expand(t_token *token);
void	ft_error(void);
void	remove_dquote(t_token *token);
char	**token_list(t_token *token);
void	parse_tokens(t_token *tokens);
char	*get_pass(char	*line);
int	token_count(t_token *token);
char	**token_list(t_token *token);
void	use_history(const char *line);
char	**parse_pipeline(char *line);
t_parser	*parser(t_token *tokens);
void	check_pipe(t_parser *parser, t_args *args);


#endif // MINISHELL_H
