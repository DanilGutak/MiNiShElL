/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 23:02:31 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/06 17:25:40 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

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
			value += replace_dollar(value, &buffer, data);
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

int	do_heredoc(t_data *data, t_cmd_table *cmd_table, int i)
{
	char		*stop;
	static int	j = -1;
	char		*itoa_res;
	char		*name;
	char		*line;
	int			fd;

	stop = cmd_table->redirs[i].value;
	itoa_res = ft_itoa(i);
	if (itoa_res == NULL)
		return (MALLOC_F);
	name = ft_strcat(".oouyhukuliyty", itoa_res);
	free(itoa_res);
	if (name == NULL)
		return (MALLOC_F);
	fd = open(name , O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd < 0)
		return (print_error(data, "Minishell: open: ", 1));
	while (++j >= 0)
	{
		line = readline("> ");
		if (line == NULL)
			return (ft_printf_fd(STDERR_FILENO, "bash: warning: here-document at line %d delimited by end-of-file (wanted `%s')", j, stop));
		if (ft_strcmp(line, stop) == 0)
			break;
		line = expand_local_token(data, line);
		if (!line)
			return (close(fd), MALLOC_F);
		ft_putendl_fd(line, fd);
		free(line);
	}
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
