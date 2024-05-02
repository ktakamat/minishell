/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:06:53 by ktakamat          #+#    #+#             */
/*   Updated: 2024/04/23 20:06:56 by ktakamat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_redirect_type
{
	UNKNOWN,
	QUOTE_HEREDOC,
	HEREDOC,
	IN_FILE,
	OUT_FILE,
	APPEND
}						t_redirect_type;

typedef struct s_file
{
	char				*file_name;
	t_redirect_type		type;
	t_file				*next;
}						t_file;

typedef struct s_parser
{
	char				**cmd;
	t_file				*file;
	t_parser			*next;
	t_parser			*prev;
}						t_parser;

#endif
