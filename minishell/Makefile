NAME = minishell
CC = CC
RM = rm -f
INCLUDES_DIR = ./includes
BUILTIN_DIR = ./srcs/built_in
LEXER_DIR = ./srcs/lexer
PARSER_DIR = ./srcs/parser
PIPEREDIRECT_DIR = ./srcs/pipe_redirect
READLINE_DIR = $(shell brew --prefix readline)
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES_DIR) -I$(READLINE_DIR)/include

SRCS = srcs/main.c \
       srcs/minishell_split.c \
       srcs/main_helper.c \
       srcs/signal_handler.c \
       srcs/env_util.c \
       $(BUILTIN_DIR)/cd.c \
       $(BUILTIN_DIR)/exit.c \
       $(BUILTIN_DIR)/pwd.c \
       $(BUILTIN_DIR)/commands.c \
       $(BUILTIN_DIR)/echo.c \
       $(BUILTIN_DIR)/env.c \
       $(BUILTIN_DIR)/env_ver.c \
       $(BUILTIN_DIR)/env_helper.c \
       $(BUILTIN_DIR)/export.c \
       $(BUILTIN_DIR)/export_helper_1.c \
       $(BUILTIN_DIR)/export_helper_2.c \
       $(BUILTIN_DIR)/execve.c \
       $(BUILTIN_DIR)/execve_helper_1.c \
       $(BUILTIN_DIR)/execve_helper_2.c \
       $(BUILTIN_DIR)/builtin.c \
       $(BUILTIN_DIR)/unset.c \
       $(LEXER_DIR)/lexer.c \
       $(LEXER_DIR)/lexer_util.c \
       $(LEXER_DIR)/token_1.c \
       $(LEXER_DIR)/token_2.c \
       $(LEXER_DIR)/token_3.c \
       $(PARSER_DIR)/parser.c \
       $(PARSER_DIR)/parser_util.c \
       $(PARSER_DIR)/redi_parser.c \
       $(PIPEREDIRECT_DIR)/pipe.c \
       $(PIPEREDIRECT_DIR)/redirect.c \
       $(PIPEREDIRECT_DIR)/dollar_handle.c \
       $(PIPEREDIRECT_DIR)/expansion_sub.c \
       $(PIPEREDIRECT_DIR)/expansion.c \
       $(PIPEREDIRECT_DIR)/quote_handle.c \
       $(PIPEREDIRECT_DIR)/sub_expansion.c

OBJS = $(SRCS:%.c=%.o)

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L$(READLINE_DIR)/lib -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re

