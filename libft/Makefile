# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 16:02:58 by dgutak            #+#    #+#              #
#    Updated: 2023/09/14 10:50:19 by dgutak           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=ft_isalpha.c ft_strlcat.c \
				ft_strncmp.c ft_strdup.c ft_isdigit.c\
				ft_isalnum.c ft_isascii.c ft_isprint.c\
				ft_tolower.c ft_toupper.c ft_atoi.c\
				ft_strchr.c ft_strrchr.c\
				ft_memcpy.c ft_memset.c ft_memmove.c\
				ft_split.c ft_printf.c\
				ft_memchr.c ft_memcmp.c \
				ft_putchar_fd.c ft_putstr_fd.c\
				ft_putendl_fd.c ft_putnbr_fd.c \
				 ft_putnbru_fd.c ft_printhex.c ft_strstr.c\
				 ft_strjoin.c ft_bzero.c ft_strlen.c ft_calloc.c\
				 ft_strnstr.c ft_strtrim.c
				
OBJS			= $(SRCS:.c=.o)

BONUS			= ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c\
				ft_lstsize.c ft_lstlast.c ft_lstdelone.c\
				ft_lstclear.c ft_lstiter.c ft_lstmap.c
					
					

BONUS_OBJS		= $(BONUS:.c=.o)



CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME			= libft.a

all:			$(NAME)
			
			

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

bonus:			$(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY:			all clean fclean re bonus