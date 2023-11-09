/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 23:02:31 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/07 15:28:04 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stdio.h>

/**
 * The function "replace_dollar" replaces a dollar sign ($) with the corresponding variable value in a
 * given string.
 * 
 * @param iterate A pointer to a character array (string) that represents the input to be processed.
 * @param result A pointer to a pointer to a character (char **), which will store the result of the
 * function.
 * @param data A pointer to a structure of type t_data.
 * @param ex The parameter "ex" is an integer that indicates whether the variable is being expanded or
 * not. If "ex" is non-zero, it means the variable is being expanded.
 * 
 * @return the length of the variable name (vlen).
 */
int	replace_dollar(char *iterate, char **result, t_data *data, int ex)
{
	const int	vlen = count_var_len(iterate);
	char		*buffer;
	char		*key;

	if (vlen == 1 && ex)
		return (*result = ft_strdup(""), vlen);
	if (vlen == 1)
		return (*result = ft_strdup("$"), vlen);
	key = ft_substr(iterate, 1, vlen - 1);
	if (key == NULL)
		return (vlen);
	buffer = get_variable_value(data, key);
	free(key);
	if (buffer == NULL)
		*result = ft_strdup("");
	else
		*result = ft_strdup(buffer);
	free(buffer);
	return (vlen);
}

/**
 * The function `expand_local_token` expands a local token by replacing any occurrences of `$` with the
 * corresponding value from the `data` structure.
 * 
 * @param data A pointer to a struct of type t_data.
 * @param value A pointer to a character array (string) that represents the value to be expanded.
 * 
 * @return a pointer to a character array (string).
 */
static char	*expand_local_token(t_data *data, char *value)
{
	char	*buf_value;
	char	*buf_res;
	char	*buffer;
	char	*res;

	res = NULL;
	buf_value = value;
	if (!*value)
		return (value);
	while (*value)
	{
		buffer = NULL;
		if (*value == '$')
			value += replace_dollar(value, &buffer, data, 0);
		else
			value += concat_chars(value, &buffer);
		if (buffer == NULL)
			return (free(res), NULL);
		buf_res = ft_strcat(res, buffer);
		(free(buffer), free(res));
		if (buf_res == NULL)
			return (NULL);
		res = buf_res;
	}
	return (free(buf_value), res);
}

/**
 * The function `get_name_heredoc` generates a temporary name for a heredoc file based on an integer
 * input.
 * 
 * @param i The parameter "i" is an integer value that is used to generate a unique name for the
 * heredoc file. It is passed to the function "ft_itoa" to convert it into a string representation. The
 * resulting string is then concatenated with the prefix ".temp_heredoc" to
 * 
 * @return a pointer to a character array (string) named "name".
 */
static char	*get_name_heredoc(int i)
{
	char		*itoa_res;
	char		*name;

	itoa_res = ft_itoa(i);
	if (itoa_res == NULL)
		return (NULL);
	name = ft_strcat(".temp_heredoc", itoa_res);
	free(itoa_res);
	return (name);
}

/**
 * The function `do_while` reads input from the user until a specific stop condition is met, and writes
 * the input to a file descriptor.
 * 
 * @param data A pointer to a data structure containing information about the program's state and
 * configuration.
 * @param fd The parameter `fd` is an integer representing the file descriptor.
 * @param stop The `stop` parameter is a string that represents the delimiter for the here-document.
 * The `do_while` function reads input from the user until it encounters a line that is equal to the
 * `stop` string.
 * 
 * @return the value "SUCCESS".
 */
static int	do_while(t_data *data, int fd, char *stop)
{
	static int	j = 0;
	char		*line;

	mode(data, HEREDOC);
	while (1)
	{
		line = readline("> ");
		if (g_signal == CNTRL_C)
			return (free(line), 1);
		if (line == NULL && ft_printf_fd(STDERR_FILENO, "minishell: warning: \
here-document at line %d delimited by end-of-file(wanted `%s')\n", j, stop))
			break ;
		if (ft_strcmp(line, stop) == 0)
			break ;
		line = expand_local_token(data, line);
		if (!line)
			return (close(fd), MALLOC_F);
		ft_putendl_fd(line, fd);
		free(line);
		j++;
	}
	mode(data, NON_INTERACTIVE);
	if (line != NULL)
		free(line);
	return (SUCCESS);
}

/**
 * The function `do_heredoc` creates a temporary file, writes the contents of a heredoc into the file,
 * and then either unlinks the file or sets it as the input file for the command table.
 * 
 * @param data A pointer to a structure of type t_data.
 * @param cmd_table A structure that contains information about the command and its redirections.
 * @param i The parameter `i` is an integer that represents the index of the current redirection in the
 * command table.
 * 
 * @return the value of the macro `SUCCESS`.
 */
int	do_heredoc(t_data *data, t_cmd_table *cmd_table, int i)
{
	char		*name;
	int			status;
	int			fd;

	name = get_name_heredoc(i);
	if (!name)
		return (print_error(data, "Malloc failed", 1), 1);
	fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd < 0)
		return (free(name), print_error(data, "Minishell: open: ", 1));
	status = do_while(data, fd, cmd_table->redirs[i].value);
	if (status == MALLOC_F || status == 1)
		return (unlink(name), free(name), 1);
	close(fd);
	if (cmd_table->redirs[i].no_space != 3)
		unlink(name);
	else
	{
		cmd_table->in_file = open(name, O_RDONLY);
		if (cmd_table->in_file == -1)
			return (free(name), print_error(data, "Minishell: open: ", 1));
		cmd_table->last_heredoc = ft_strdup(name);
	}
	free(name);
	return (SUCCESS);
}
