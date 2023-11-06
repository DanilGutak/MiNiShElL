/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:21:13 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/06 19:43:43 by dgutak           ###   ########.fr       */
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
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
// for errno
# include <errno.h>

# define SUCCESS 0
# define FAILURE 1
# define MALLOC_F 2

# define KEEP_GOING 0
# define CNTRL_C 1
# define CNTRL_S 2

extern int			g_signal;

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

typedef enum s_mode
{
	INTERACTIVE,
	NON_INTERACTIVE,
	CHILD
}					t_mode;

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
	int				in_file;
	int				out_file;
	int				num_redirs;
	int				num_args;
	int				is_child_created;
	int				is_failed;
	char			*last_heredoc;
	pid_t			pid;
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
	int				exit_code;
	int				prev_fd;
	int				original_stdin;
	int				original_stdout;
	t_mode			mode;
}					t_data;

// signals

void				setup_signals(t_data *data);
void				mode(t_data *data, t_mode mode);

// heredoc

int					do_heredoc(t_data *data, t_cmd_table *cmd_table, int i);

// init

void				data_init(t_data *data, char **envp);
char				**get_path(t_data *data, int i);
void				create_original_fds(t_data *data);

// errors

void				exit_shell(t_data *data, int exit_code);
void				syntax_error(int code, t_data *data);
void				free_double_p(char **p);
void				free_all(t_data *data);
int					print_error(t_data *data, char *str, int mode);
// lexer

int					lexer(t_data *data);
int					fill_quotes(t_data *data, char const *s, char temp);
int					fill_word(t_data *data, char const *s);
int					realloc_tokens(t_data *data, int token_max);
int					free_tokens(t_token *tokens, int token_max, t_data *data);

// parser

int					parser(t_data *data);
int					is_arg(t_token_type type);
int					is_not_redir(t_token_type type);
int					fill_cmd_args(t_data *data, int j, int i);
int					fill_redirs(t_data *data, int j, int i);
int					count_pipes(t_data *data);
int					count_new_tokens(t_data *data);
int					merge_words(t_data *data);

// executor

void				executor(t_data *data);
int					find_executable(t_data *data, t_cmd_table *cmd_table);
void				set_dups(t_cmd_table *cmd_table);
int					check_builtin(t_cmd_table *cmd_table);
void				execute_builtin(t_data *data, t_cmd_table *cmd_table, int i,
						int *pipe_fd);
int					set_fd_in_out(t_data *data, t_cmd_table *cmd_table, int *fd,
						int i);
void				wait_children(t_data *data);
int					fake_pipes(t_data *data, int i, int *pip);
int					exist_in_dir(t_data *data, t_cmd_table *cmd_table);
int					look_in_dir(t_data *data, t_cmd_table *cmd_table);
// expander

int					expander(t_data *data);
int					count_var_len(const char *value);
int					replace_dollar(char *iterate, char **result, t_data *data,
						int ex);
int					concat_chars(char *iterate, char **result);

// cleaner

void				clean_stuff(t_data *data);
void				clean_all(t_data *data);

// variables api, for buildins and so on

int					increment_shlvl_variable(t_data *data);
int					get_variable_numb(char **envp, char *name);
char				*get_variable(char **envp, char *name);
int					starts_with(char *string, char *begin);
int					append_variable(t_data *data, char *key, char *value);
int					create_variable(t_data *data, char *key, char *value);
int					is_valid_key(char *key);
int					delete_variable(t_data *data, char *key);
char				*get_variable_value(t_data *data, char *key);
int					set_variable(t_data *data, char *key, char *value);

// builtins

void				builtin_echo(t_data *data, t_cmd_table *cmd_table);
void				builtin_exit(t_data *data, t_cmd_table *cmd_table);
int					builtin_cd(t_data *data, t_cmd_table *cmd_table);
void				builtin_unset(t_data *data, t_cmd_table *cmd_table);
void				builtin_env(t_data *data, t_cmd_table *cmd_table);
void				builtin_export(t_data *data, t_cmd_table *cmd_table);
void				builtin_pwd(t_data *data);

#endif
