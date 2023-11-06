/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 23:02:31 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/06 21:36:23 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

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

static char	*expand_local_token(t_data *data, char *value)
{
	char	*buf_value;
	char	*buf_res;
	char	*buffer;
	char	*res;

	res = NULL;
	buf_value = value;
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
	free(buf_value);
	return (res);
}

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

static int	do_while(t_data *data, int fd, char *stop)
{
	static int	j = 0;
	char		*line;

	mode(data, INTERACTIVE);
	while (1)
	{
		line = readline("> ");
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

int	do_heredoc(t_data *data, t_cmd_table *cmd_table, int i)
{
	char		*name;
	int			status;
	int			fd;

	name = get_name_heredoc(i);
	if (!name)
		return (MALLOC_F);
	fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd < 0)
		return (print_error(data, "Minishell: open: ", 1));
	status = do_while(data, fd, cmd_table->redirs[i].value);
	if (status == MALLOC_F)
		return (MALLOC_F);
	close(fd);
	if (cmd_table->redirs[i].no_space != 3)
		unlink(name);
	else
	{
		cmd_table->in_file = open(name, O_RDONLY);
		if (cmd_table->in_file == -1)
			return (print_error(data, "Minishell: open: ", 1));
		cmd_table->last_heredoc = ft_strdup(name);
	}
	free(name);
	return (SUCCESS);
}
