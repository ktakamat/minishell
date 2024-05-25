NAME = minishell
CC = CC
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDES_DIR = ./includes
BUILTIN_DIR = ./srcs/built_in
LEXER_DIR = ./srcs/lexer
PARSER_DIR = ./srcs/parser
PIPEREDIRECT_DIR = ./srcs/pipe_redirect

SRCS = srcs/main.c \
	   srcs/minishell_split.c \
       $(BUILTIN_DIR)/chdir.c \
       $(BUILTIN_DIR)/exit.c \
	   $(BUILTIN_DIR)/pwd.c \
	   $(BUILTIN_DIR)/commands.c \
	   $(BUILTIN_DIR)/echo.c \
	   $(BUILTIN_DIR)/env.c \
	   $(LEXER_DIR)/lexer.c \
	   $(PARSER_DIR)/parser.c \
	   $(PIPEREDIRECT_DIR)/pipe.c \
	   $(PIPEREDIRECT_DIR)/redirect.c \
	   

OBJS = $(SRCS:%.c=%.o)

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

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
