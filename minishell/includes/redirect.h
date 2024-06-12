/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:03:12 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/10 18:00:44 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "./minishell.h"
# include "./directory.h"
# include "./builtin.h"

# define MAX_BUFFER_SIZE 4096
# define FILE_MODE	0644
# define PIPE_WRITE	1
# define PIPE_READ	0
# define FAILURE 1
# define SUCCESS 0
# define NO_FILENAME "minishell: syntax error near unexpected token `newline'\n"

typedef enum e_redirect_type
{
	INPUT_REDI,
	OUTPUT_REDI,
	APPEND_OUTPUT_REDI,
	HEREDOC_REDI,
}						t_redirect_type;

typedef enum e_parse_state
{
	STATE_NORMAL,
	STATE_IN_DQUOTE
}	t_parse_state;

typedef struct s_redirect
{
	t_redirect_type		type;
	int					fd;
	int					fd_file;
	int					fd_backup;
	char				*file_name;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_parse_context
{
	char		*str;
	size_t		i;
	char		*result;
	int			j;
	t_directory	*dir;
	t_env	**env_var;
}	t_parse_context;

typedef struct s_expand
{
	char	*start;
	char	*end;
	char	*value;
	char	*temp;
	int		flag;
}	t_expand;

#endif