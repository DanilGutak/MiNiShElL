/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 23:02:31 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/06 15:35:02 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

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

void	do_heredoc(t_data *data, t_cmd_table *cmd_table, int i, int useless)
{
	const char	*stop = cmd_table->redirs[i].value;
	char		*line;
	int			fd;

	fd = open(stop, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd < 0)
		return ((void)(data->exit_code = 1));
	line = get_next_line(STDIN_FILENO, READ);
	if (line == NULL)
		return ((void)(close(fd)));
	while (ft_strcmp(line, stop) != 0)
	{
		line = expand_local_token(data, line);
		if (!line)
			return ((void)(close(fd), get_next_line(fd, CLEAN)));
		ft_putendl_fd(line, fd);
		free(line);
		line = get_next_line(STDIN_FILENO, READ);
		if (line == NULL)
			return ((void)(close(fd), get_next_line(fd, CLEAN)));
	}
	free(line);
	get_next_line(fd, CLEAN);
	close(fd);
	if (useless)
		unlink(stop);
	else
	{
		cmd_table->in_file = open(stop, O_RDONLY);
		if (cmd_table->in_file == -1)
			perror("kek");
	}
}
