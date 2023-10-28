# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 16:02:58 by dgutak            #+#    #+#              #
<<<<<<< Updated upstream
#    Updated: 2023/10/28 18:26:34 by vfrants          ###   ########.fr        #
=======
#    Updated: 2023/10/28 18:39:40 by dgutak           ###   ########.fr        #
>>>>>>> Stashed changes
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
NAME	= libft.a

SRCS	= \
		ft_memset.c ft_bzero.c ft_memcpy.c ft_striteri.c ft_memmove.c \
		ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
		ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_math_i.c ft_contains.c get_next_line.c ft_strcat.c ft_free.c \
<<<<<<< Updated upstream
		ft_is_blank.c ft_free_split.c \
		ft_printf.c ft_putnbru_fd.c ft_printhex.c ft_strstr.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c \
		ft_lstsize.c ft_lstlast.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c
=======
		ft_is_blank.c ft_free_split.c ft_strcmp.c \
		ft_printf.c ft_putnbru_fd.c ft_printhex.c ft_strstr.c
>>>>>>> Stashed changes

OBJS	= $(SRCS:.c=.o)

%.o		: %.c
		${CC} ${CFLAGS} -c $< -o $@ -I .

all		: ${NAME}

$(NAME) : ${OBJS}
		ar rcs ${NAME} ${OBJS}

clean	:
		$(RM) $(OBJS)

fclean	: clean
		$(RM) $(NAME)

re		: fclean $(NAME)

.PHONY	: all clean fclean re
.SILENT :
