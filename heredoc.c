/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 23:02:31 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/04 23:10:12 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_heredoc(t_data *data, t_cmd_table *cmd_table, int i)
{
	const char	*stop = cmd_table->redirs[i].value;
	char		*line;
	int			fd;

	fd = open(stop, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return ((void)(data->exit_code = 1));
	line = get_next_line(STDIN_FILENO, READ);
	if (line == NULL)
		return ((void)(close(fd)));
	while (ft_strcmp(line, stop) != 0)
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = get_next_line(STDIN_FILENO, READ);
		if (line == NULL)
			return ((void)(close(fd), get_next_line(fd, CLEAN)));
	}
	free(line);
	get_next_line(fd, CLEAN);
	cmd_table->fd_in = fd;
}
