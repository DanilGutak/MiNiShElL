/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:53:21 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/06 20:06:20 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function sets the input and output file descriptors for a command table based on the specified
 * input and output files or the previous and next file descriptors.
 * 
 * @param data A pointer to a struct called "t_data".
 * @param cmd_table A structure containing information about the command being executed, such as input
 * and output file descriptors.
 * @param fd The parameter `fd` is an integer array that represents file descriptors. It is used to
 * pass file descriptors between different commands in a pipeline.
 * @param i The parameter "i" represents the index of the current command table in the array of command
 * tables.
 * 
 * @return 0.
 */
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

/**
 * The function "wait_children" waits for child processes to finish and updates the exit code based on
 * the status of the child processes.
 * 
 * @param data A pointer to a structure of type t_data.
 */
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

/**
 * The function `fake_pipes` handles the redirection of input and output for a command in a pipeline.
 * 
 * @param data A pointer to a struct called "t_data" which contains various data related to the
 * program.
 * @param i The parameter `i` represents the index of the current command in the `cmdt` array.
 * @param pip The `pip` parameter is a pointer to an integer array that represents a pipe. The pipe is
 * used for inter-process communication between the parent process and the child process. The array
 * contains two file descriptors: `pip[0]` for reading from the pipe and `pip[1]` for
 * 
 * @return 1.
 */
int	fake_pipes(t_data *data, int i, int *pip)
{
	if (data->cmdt[i].fd_in != -1
		&& dup2(data->cmdt[i].fd_in, STDIN_FILENO) > -1)
		close(data->cmdt[i].fd_in);
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
	if (data->cmdt[i].fd_in != -1)
		close(data->cmdt[i].fd_in);
	if (data->cmdt[i].fd_out != -1)
		close(data->cmdt[i].fd_out);
	if (data->cmdt[i].last_heredoc)
	{
		unlink(data->cmdt[i].last_heredoc);
		free(data->cmdt[i].last_heredoc);
	}
	return (1);
}

/**
 * The function "look_in_dir" checks if a command is executable in the current directory or in the
 * specified path.
 * 
 * @param data A pointer to a structure of type t_data.
 * @param cmd_table The `cmd_table` parameter is a pointer to a structure of type `t_cmd_table`.
 * 
 * @return an integer value.
 */
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

/**
 * The function checks if a command exists in the current directory or in the PATH environment
 * variable.
 * 
 * @param data A pointer to a structure of type t_data.
 * @param cmd_table A structure that contains information about the command being executed, such as the
 * command itself (cmd_table->cmd).
 * 
 * @return an integer value.
 */
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
