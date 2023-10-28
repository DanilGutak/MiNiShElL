/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:21:13 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/28 22:34:46 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
// for readline
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
// for errno
# include <errno.h>

# define SUCCESS 0
# define FAILURE 1

typedef enum s_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	DQUOTE,
	SQUOTE
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				no_space;
}					t_token;

typedef struct s_cmd_table
{
	char			*cmd;
	char			**args;
	int				fd_in;
	int				fd_out;
	t_token			*redirs;
	int				num_redirs;
	int				num_args;
}					t_cmd_table;

typedef struct s_data
{
	char			**envp;
	char			**path;
	char			*input;
	t_token			*tokens;
	int				token_count;
	int				token_max;
	t_cmd_table		*cmdt;
	int				cmdt_count;
	int				pip[2];
	int				exit_code;
}					t_data;

// init

void				data_init(t_data *data, char **envp);
char				**get_path(t_data *data, int i);

// errors

void				exit_shell(t_data *data, int exit_code);
void				syntax_error(int code);
void				free_double_p(char **p);
void				builtin_exit(t_data *data, t_cmd_table *cmd_table);
void				free_all(t_data *data);

// lexer

int					lexer(t_data *data);
int					fill_quotes(t_data *data, char const *s, char temp);
int					fill_word(t_data *data, char const *s);
void				realloc_tokens(t_data *data, int token_max);
void				free_tokens(t_token *tokens, int token_max, t_data *data);

// parser

int					parser(t_data *data);
int					is_arg(t_token_type type);
int					is_not_redir(t_token_type type);
int					fill_cmd_args(t_data *data, int j, int i);
void				fill_redirs(t_data *data, int j, int i);

// executor

void				executor(t_data *data);

// cleaner

void				clean_stuff(t_data *data);

// variables api, for buildins and so on

char	*get_variable(char **envp, char *name);
int		get_variable_numb(char **envp, char *name);
int		starts_with(char *string, char *begin);
int		increment_shlvl_variable(char **envp);

#endif
