/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:09:50 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/02 15:28:19 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>

void	set_dups(t_cmd_table *cmd_table)
{
	if (cmd_table->fd_in != -1)
		dup2(cmd_table->fd_in, STDIN_FILENO);
	if (cmd_table->fd_out != -1)
		dup2(cmd_table->fd_out, STDOUT_FILENO);
}
void	execute_command(t_data *data, t_cmd_table *cmd_table, int i)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit_shell(data, 1);
	cmd_table->pid = fork();
	if (cmd_table->pid < 0)
		exit_shell(data, 1);
	if (!cmd_table->pid)
	{
		if (i != 0)
		{
			dup2(data->prev_fd, STDIN_FILENO);
			close(data->prev_fd);
		}
		if (i != data->cmdt_count - 1)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		execve(cmd_table->cmd, cmd_table->args, data->envp);
		print_error(data, cmd_table->cmd, 1);
		exit(1);
	}
	close(pipe_fd[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (i != data->cmdt_count - 1)
		data->prev_fd = pipe_fd[0];
	else
		close(pipe_fd[0]);
}

int	execute_builtin(t_data *data, t_cmd_table *cmd_table)
{
	int	returno;

	returno = 0;
	/* if (ft_strcmp(cmd_table->cmd, "echo") == 0)
		return (builtin_echo(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "cd") == 0)
		return (builtin_cd(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "pwd") == 0)
		return (builtin_pwd(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "export") == 0)
		return (builtin_export(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "unset") == 0)
		return (builtin_unset(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "env") == 0)
		return (builtin_env(data, cmd_table));  */
	if (ft_strcmp(cmd_table->cmd, "exit") == 0 && ++returno)
		builtin_exit(data, cmd_table);
	return (returno);
}

/* int set_fd_in_out(t_data *data, t_cmd_table *cmd_table, int *fd)
{
	if (cmd_table->in_file)
} */

void	executor(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	data->prev_fd = -1;
	// open redirs here
	// set infile and outfile here
	while (++i < data->cmdt_count)
	{
		/* if pipit
		if (set_fd_in_out(data, &data->cmdt[i]) == 1)
			return ; */
		if (execute_builtin(data, &data->cmdt[i]) == 0)
		{
			if (find_executable(data, &data->cmdt[i]) == 0)
			{
				data->cmdt[i].is_child_created = 1;
				execute_command(data, &data->cmdt[i], i);
			}
		}
	}
	i = -1;
	while (++i < data->cmdt_count)
		waitpid(data->cmdt[i].pid, &status, 0);
	if (data->cmdt[i - 1].is_child_created == 1)
		data->exit_code = WEXITSTATUS(status);
}
