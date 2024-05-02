# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 19:38:26 by ktakamat          #+#    #+#              #
#    Updated: 2024/04/23 20:00:33 by ktakamat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
INCLUDES_DIR = ./includes
BUILTIN_DIR = ./srcs/built_in
LP_DIR = ./srcs/lexer_parser
CFLAGS =-I$(INCLUDES_DIR)
SRCS =	./srcs/main.c \
		$(LP_DIR)/lexer.c \
		# ./srcs/signalctrl.c \
		# $(BUILTIN_DIR)/cd.c \
		# ./srcs/execute.c \
		

OBJS = $(SRCS:%.c=%.o)

LIBDIR = ./libft
LIBFT = $(LIBDIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBDIR)

clean:
	$(MAKE) clean -C $(LIBDIR)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBDIR)
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re