# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yususato <yususato@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 16:12:07 by yususato          #+#    #+#              #
#    Updated: 2024/07/02 17:51:59 by yususato         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

INCL = libft.h

CC = cc

CFLAG = -Wall -Wextra -Werror

SRCS = ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strjoin.c \
		ft_strdup.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_strtrim.c \
		ft_split.c \
		ft_substr.c \
		ft_atoi.c \
		ft_itoa.c \
		ft_printf.c \
		ft_printf_uni.c \
		printf_tool.c
		


BONUS_SRCS = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstdelone.c \
			ft_lstadd_back.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

ifdef WITH_BONUS
	SRCS += $(BONUS_SRCS)
	OBJS += $(BONUS_OBJS)
endif

all : $(NAME)
$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o: %.c $(INCL)
	$(CC) $(CFLAG) -c $< -o $@ -I$(INCL)


clean : 
	rm -f $(OBJS) $(BONUS_OBJS)

fclean : clean 
	rm -f $(NAME)

bonus :
	make WITH_BONUS=1;

re : fclean all
