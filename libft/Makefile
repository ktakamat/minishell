# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktakamat <ktakamat@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 21:10:02 by machi             #+#    #+#              #
#    Updated: 2024/04/25 20:08:33 by ktakamat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCL)
INCL = libft.h
SRCS = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_exit.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strcmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c

OBJS = $(SRCS:%.c=%.o)

SRCS += ft_print_char.c \
		ft_print_hex.c \
		ft_print_ptr.c \
		ft_printf.c \
		ft_print_str.c \
		ft_print_unbr.c \
		ft_print_nbr.c
OBJS += ft_print_char.o \
		ft_print_hex.o \
		ft_print_ptr.o \
		ft_printf.o \
		ft_print_str.o \
		ft_print_unbr.o \
		ft_print_nbr.o
INCL += -Ift_printf.h

# SRCS += ./gnl/get_next_line_utils.c \
# 		./gnl/get_next_line_main.c \
# 		./gnl/kusottare.c
# OBJS += ./gnl/get_next_line_utils.o \
# 		./gnl/get_next_line_main.o \
# 		./gnl/kusottare.o
# INCL += -Iget_next_line.h

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
