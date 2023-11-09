/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:09:50 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/06 21:30:19 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

/**
 * The function "clean_fds" closes file descriptors and deletes temporary files used for input/output
 * redirection in a command table.
 * 
 * @param data A pointer to a structure of type t_data.
 * @param cmd_table A structure that contains file descriptors for input and output, as well as
 * information about the last heredoc used.
 * @param i The parameter "i" is an integer that represents the index of the command in the command
 * table.
 */
void	clean_fds(t_data *data, t_cmd_table *cmd_table, int i)
{
	if (cmd_table->fd_in != -1)
		close(cmd_table->fd_in);
	if (cmd_table->fd_out != -1)
		close(cmd_table->fd_out);
	if (data->cmdt[i].last_heredoc)
	{
		unlink(data->cmdt[i].last_heredoc);
		free(data->cmdt[i].last_heredoc);
	}
}

/**
 * The function executes a command by forking a child process, setting up input and output redirection,
 * and executing the command using execve.
 * 
 * @param data A pointer to a data structure that contains various information needed for executing the
 * command.
 * @param cmd_table A structure that contains information about the command to be executed, such as the
 * command itself, arguments, file descriptors for input and output, and the process ID of the child
 * process.
 * @param i The parameter `i` is an integer that represents the index of the current command in the
 * command table. It is used to determine if the current command is the last command in the command
 * table.
 * @param pipe_fd The `pipe_fd` parameter is an array of file descriptors used for inter-process
 * communication. It is used to pass data between the parent process and the child process created by
 * the `fork()` system call. The array contains two file descriptors: `pipe_fd[0]` is used for reading
 * from
 * 
 * @return void, which means it is not returning any value.
 */
void	execute_command(t_data *data, t_cmd_table *cmd_table, int i,
		int *pipe_fd)
{
	cmd_table->pid = fork();
	if (cmd_table->pid < 0)
		return ((void)print_error(data, "fork", 1));
	if (!cmd_table->pid)
	{
		if (cmd_table->fd_in != -1 && dup2(cmd_table->fd_in, STDIN_FILENO))
			close(cmd_table->fd_in);
		close(pipe_fd[0]);
		if (cmd_table->fd_out != -1 && dup2(cmd_table->fd_out, STDOUT_FILENO))
			close(cmd_table->fd_out);
		mode(data, CHILD);
		execve(cmd_table->cmd, cmd_table->args, data->envp);
		print_error(data, cmd_table->cmd, 1);
		clean_all(data);
		exit(1);
	}
	close(pipe_fd[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (i != data->cmdt_count - 1)
		data->prev_fd = pipe_fd[0];
	else
		close(pipe_fd[0]);
	clean_fds(data, cmd_table, i);
}


/**
 * The function `other_redirs` handles output redirection in a command table structure.
 * 
 * @param data A pointer to a data structure that contains some information needed for the function.
 * @param cmd_table A pointer to a structure that represents a command table. The command table
 * contains information about the command to be executed, including any redirections that need to be
 * performed.
 * @param i The parameter `i` is an integer that represents the index of the redirection in the
 * `cmd_table->redirs` array.
 * 
 * @return an integer value.
 */
int	other_redirs(t_data *data, t_cmd_table *cmd_table, int i)
{
	if (cmd_table->redirs[i].type == REDIR_OUT)
	{
		if (cmd_table->out_file != -1)
			close(cmd_table->out_file);
		cmd_table->out_file = open(cmd_table->redirs[i].value,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd_table->out_file == -1)
			return (print_error(data, cmd_table->redirs[i].value, 1));
	}
	else if (cmd_table->redirs[i].type == REDIR_APPEND)
	{
		if (cmd_table->out_file != -1)
			close(cmd_table->out_file);
		cmd_table->out_file = open(cmd_table->redirs[i].value,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd_table->out_file == -1)
			return (print_error(data, cmd_table->redirs[i].value, 1));
	}
	else if (cmd_table->redirs[i].type == REDIR_HEREDOC)
		if (do_heredoc(data, cmd_table, i) == 1)
			return (1);
	return (0);
}
/**
 * The function `manage_redirs` handles input/output redirection for a command table in a shell
 * program.
 * 
 * @param data A pointer to a data structure containing information about the shell environment.
 * @param cmd_table A structure that contains information about the command and its redirections. It
 * includes fields such as `redirs` (an array of redirections), `out_file` (the file descriptor for
 * output redirection), `in_file` (the file descriptor for input redirection), and `num_redirs` (
 * @param i The variable `i` is used as a loop counter in the `manage_redirs` function. It is
 * incremented in each iteration of the loop to iterate over the `redirs` array of the `cmd_table`
 * structure.
 * 
 * @return The function `manage_redirs` returns an integer value.
 */
int	manage_redirs(t_data *data, t_cmd_table *cmd_table)
{
	int	i;

	i = -1;
	while (++i < cmd_table->num_redirs)
	{
		if (cmd_table->redirs[i].no_space == 2
			&& cmd_table->redirs[i].type != REDIR_HEREDOC)
		{
			ft_printf_fd(2, "minishell: ambigious redirect\n");
			return (1);
		}
		if (cmd_table->redirs[i].type == REDIR_IN)
		{
			if (cmd_table->in_file != -1)
				close(cmd_table->in_file);
			cmd_table->in_file = open(cmd_table->redirs[i].value, O_RDONLY);
			if (cmd_table->in_file == -1)
				return (print_error(data, cmd_table->redirs[i].value, 1));
		}
		else if (other_redirs(data, cmd_table, i) == 1)
			return (1);
	}
	return (0);
}

/**
 * The function "executor" executes a series of commands, managing pipes and redirections as necessary.
 * 
 * @param data A pointer to a struct that contains various data needed for the execution of commands.
 * 
 * @return The function does not have a return type, so nothing is being returned.
 */
void	executor(t_data *data)
{
	int	i;
	int	pip[2];

	i = -1;
	data->prev_fd = -1;
	while (++i < data->cmdt_count)
	{
		if (pipe(pip) == -1)
			return ((void)print_error(data, "pipe", 1));
		if (manage_redirs(data, &data->cmdt[i]) == 1 && fake_pipes(data, i,
				pip))
			continue ;
		set_fd_in_out(data, &data->cmdt[i], pip, i);
		if (check_builtin(&data->cmdt[i]) == 1)
			execute_builtin(data, &data->cmdt[i], i, pip);
		else
		{
			if (find_executable(data, &data->cmdt[i]) == 0
				&& ++data->cmdt[i].is_child_created)
				execute_command(data, &data->cmdt[i], i, pip);
			else
				fake_pipes(data, i, pip);
		}
	}
	wait_children(data);
}
