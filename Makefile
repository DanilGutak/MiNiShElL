# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 17:55:20 by dgutak            #+#    #+#              #
#    Updated: 2023/10/23 17:35:44 by dgutak           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L./libft -lft -lreadline

NAME = minishell
LIBFT	=	./libft/libft.a
LEX = lexer.c fill_tokens.c
PARS = parser.c



SRCS = main.c init.c exit.c exit_shell.c $(LEX) $(PARS) error.c 
OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft/
	$(CC) $(CFLAGS) $(LIBFT) -o $(NAME) $(OBJS) $(LDFLAGS)

.c.o:
	cc $(CFLAGS) -c $< -o $(<:.c=.o)  -I ./include -I ./libft

clean:
	rm -f $(OBJS)
	make clean -C ./libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft/

re: fclean all

.PHONY: all clean fclean re
