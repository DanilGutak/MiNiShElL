# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 17:55:20 by dgutak            #+#    #+#              #
#    Updated: 2023/11/01 19:16:17 by vfrants          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
LDFLAGS	= -L ./libft -lft -lreadline

NAME	= minishell

LIBDIR	= ./libft
LIBFT	= ${LIBDIR}/libft.a

LEX		= lexer.c fill_tokens.c
PARS	= parser.c parser_utils.c redirs_and_args.c
EXEC	= executor.c find_executable.c
BUILDS	= enviroment_api.c enviroment_api_2.c builtin_exit.c
EXPANDER	= expander.c

SRCS	= main.c init.c exit_shell.c \
		$(LEX) $(PARS) $(EXEC) $(BUILDS) $(EXPANDER) error.c
OBJS	= ${SRCS:.c=.o}

all		: $(NAME)

$(NAME)	: ${LIBFT} ${OBJS}
	$(CC) $(CFLAGS) -o $@ ${OBJS} $(LDFLAGS)

%.o		: %.c
	cc $(CFLAGS) -c $< -o $@ -I ${LIBDIR}

clean	:
	rm -f $(OBJS)
	make --no-print-directory -C ${LIBDIR} clean

fclean	: clean
	rm -f $(NAME)
	make --no-print-directory -C ${LIBDIR} fclean

re		: fclean all

${LIBFT}:
	make --no-print-directory -C ${LIBDIR} all

generate_test:
	valgrind --leak-check=full --show-reachable=yes --error-limit=no --gen-suppressions=all --log-file=$(NAME).log ./$(NAME)

test	: all
	clear; valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no --suppressions=./$(NAME).supp ./$(NAME)

.PHONY: all clean fclean re test generate_test
