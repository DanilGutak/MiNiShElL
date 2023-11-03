/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:53:21 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/03 17:57:03 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_fd_in_out(t_data *data, t_cmd_table *cmd_table, int *fd, int i)
{
	if (cmd_table->in_file != -1)
		cmd_table->fd_in = cmd_table->in_file;
	else if (i != 0 && data->prev_fd != -1)
		cmd_table->fd_in = data->prev_fd;
	if (cmd_table->out_file != -1)
		cmd_table->fd_out = cmd_table->out_file;
	else if (i != data->cmdt_count - 1 && fd[1] != -1)
		cmd_table->fd_out = fd[1];
	return (0);
}

void	wait_children(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->cmdt_count)
		if (data->cmdt[i].is_child_created == 1)
			waitpid(data->cmdt[i].pid, &status, 0);
	if (data->cmdt[i - 1].is_child_created == 1)
		data->exit_code = WEXITSTATUS(status);
}

int	fake_pipes(t_data *data, int i, int *pip)
{
	if (data->cmdt[i].fd_in != -1)
	{
		dup2(data->cmdt[i].fd_in, STDIN_FILENO);
		close(data->cmdt[i].fd_in);
	}
	if (data->cmdt[i].fd_out != -1)
		dup2(data->cmdt[i].fd_out, STDOUT_FILENO);
	close(pip[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (i != data->cmdt_count - 1)
		data->prev_fd = pip[0];
	else
		close(pip[0]);
	dup2(data->original_stdout, STDOUT_FILENO);
	dup2(data->original_stdin, STDIN_FILENO);
	return (1);
}
