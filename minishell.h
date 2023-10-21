/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:21:13 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/21 21:03:27 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
// for readline
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
// for errno
# include <errno.h>

typedef enum s_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HERE_DOC,
	DQUOTE,
	SQUOTE
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}					t_token;

typedef struct s_data
{
	char			**envp;
	char			**path;
	char			*input;
	t_token			*tokens;
	int				token_count;
	int				token_max_count;
}					t_data;
void				exit_shell(t_data *data, int exit_code, char *temp);
void				data_init(t_data *data, char **envp);
void				syntax_error(t_data *data, char *msg);
char				**get_path(t_data *data, int i);
void				free_double_p(char **p);
void				exit2(t_data *data, int exit_code);
void				free_all(t_data *data);
void				lexer(t_data *data);

#endif