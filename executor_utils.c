/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:53:21 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/06 14:50:38 by dgutak           ###   ########.fr       */
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
	{
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_code = WTERMSIG(status) + 128;
	}
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

int	look_in_dir(t_data *data, t_cmd_table *cmd_table)
{
	char	*temp;
	char	*ret;

	if (data->path != NULL)
		return (1);
	if (cmd_table->cmd[0] == '\0')
		return (1);
	temp = ft_strdup("./");
	if (!temp)
		return (print_error(data, "ft_strdup", 1) + 1);
	ret = ft_strjoin(temp, cmd_table->cmd);
	if (!ret)
		return (print_error(data, "ft_strjoin", 1) + 1);
	if (access(ret, X_OK) == 0)
	{
		temp = cmd_table->cmd;
		cmd_table->cmd = ret;
		free(temp);
		return (0);
	}
	free(ret);
	return (1);
}

int	exist_in_dir(t_data *data, t_cmd_table *cmd_table)
{
	char	*ret;
	char	*temp;

	if (data->path != NULL)
		return (1);
	temp = ft_strdup("./");
	if (!temp)
		return (print_error(data, "ft_strdup", 1) + 1);
	ret = ft_strjoin(temp, cmd_table->cmd);
	if (!ret)
		return (print_error(data, "ft_strjoin", 1) + 1);
	if (access(ret, F_OK) == 0)
	{
		temp = cmd_table->cmd;
		cmd_table->cmd = ret;
		free(temp);
		ft_printf_fd(2, "minishell: %s: Permission denied\n", cmd_table->cmd);
		data->exit_code = 126;
		return (0);
	}
	free(ret);
	return (1);
}
