/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:09:50 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/30 16:17:29 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>

void	execute_command(t_data *data, t_cmd_table *cmd_table, int i)
{
	pid_t	process1;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
        exit_shell(data, 1);
	process1 = fork();
	if (process1 < 0)
		exit_shell(data, 1);
	if (!process1)
	{
		if (i != 0) 
		{
			dup2(data->prev_fd, STDIN_FILENO);
			close(data->prev_fd);  // Close the read end of the pipe
		}
		if (i != data->cmdt_count - 1) 
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);  // Close the write end of the pipe
		}
		execve(cmd_table->cmd, cmd_table->args, data->envp);
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(cmd_table->cmd, 2);
		perror(" ");
		clean_stuff(data);
		exit(1);
	}
	close(pipe_fd[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	data->prev_fd = pipe_fd[0];
	
	
}

int	execute_builtin(t_data *data, t_cmd_table *cmd_table)
{
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
		return (builtin_env(data, cmd_table)); */
	if (ft_strcmp(cmd_table->cmd, "exit") == 0)
		return (builtin_exit(data, cmd_table), 1);
	return (0);
}

void	executor(t_data *data)
{
	int		i;
	int		pipe_fd[2];


	i = -1;
	if (pipe(pipe_fd) == -1)
			exit_shell(data, 1);
	data->prev_fd = -1;
	while (++i < data->cmdt_count)
	{
		if (execute_builtin(data, &data->cmdt[i]) == 1 || find_executable(data,
				&data->cmdt[i]) == 1)
			continue ;
		execute_command(data, &data->cmdt[i], i);
	}
	i = -1;
	while (++i < data->cmdt_count)
        wait(NULL);
}
