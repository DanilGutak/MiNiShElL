# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 17:55:20 by dgutak            #+#    #+#              #
#    Updated: 2023/11/02 15:25:44 by dgutak           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror -g -MD -MP
LDFLAGS	= -L ./libft -lft -lreadline

LIBDIR		= ./libft
LIBFT		= ${LIBDIR}/libft.a

LEXER		= lexer.c fill_tokens.c
PARSER		= parser.c parser_utils.c redirs_and_args.c
EXECUTOR	= executor.c find_executable.c
BUILDINS	= enviroment_api.c enviroment_api_2.c builtin_exit.c
EXPANDER	= expander.c

SRCS	= main.c init.c exit_shell.c init_utils.c\
		$(LEXER) $(PARSER) $(EXECUTOR) $(BUILDINS) $(EXPANDER) error.c

OBJS_DIR	= objs
OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
DEPS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.d))

all		: $(NAME)

$(NAME)	: ${OBJS}
		make --no-print-directory -C ${LIBDIR} all
		$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

objs/%.o	: %.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} -c $< -o $@ -I .

clean	:
		make --no-print-directory -C ${LIBDIR} clean
		$(RM) $(OBJS_DIR)

fclean	:
		make --no-print-directory -C ${LIBDIR} fclean
		$(RM) $(OBJS_DIR) $(NAME)

re		: fclean all

generate_test:
	valgrind --leak-check=full --show-reachable=yes --error-limit=no --gen-suppressions=all --log-file=$(NAME).log ./$(NAME)

test	: all
	clear; valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no --suppressions=./$(NAME).supp ./$(NAME)

-include $(DEPS)

.PHONY: all clean fclean re test generate_test
