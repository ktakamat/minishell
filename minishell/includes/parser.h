/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:06:53 by ktakamat          #+#    #+#             */
/*   Updated: 2024/06/27 17:04:37 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./minishell.h"
# include "./redirect.h"
# include "./directory.h"

# define PIPE_ERROR "minishell: syntax error near unexpected token `|'\n"

typedef enum e_type
{
	CMD,
	PIPE
}						t_type;

typedef struct s_file
{
	char				*file_name;
	t_redirect_type		type;
	struct s_file		*next;
}						t_file;

typedef struct s_parser
{
	t_type				type;
	char				**cmd;
	t_file				*file;
	t_redirect			*redirect;
	struct s_parser		*right;
	struct s_parser		*left;
}						t_parser;

#endif
