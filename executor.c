/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:09:50 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/28 17:04:23 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* tries to find the command to execute,
	better explanation of bash logic is in README
but if slash is present tries to run command as it is,
	otherwise tries to connect with dirs from PAtTH */
int	find_executable(t_data *data, t_cmd_table *cmd_table)
{
	char	*ret;
	char	*temp;
	int		i;

	i = 0;
	if (!cmd_table->cmd || !*cmd_table->cmd)
		return (1);
	if (ft_strchr(cmd_table->cmd, '/') != 0 && access(cmd_table->cmd,
			F_OK) == 0)
		return (0);
	while (data->path[i])
	{
		temp = ft_strdup(data->path[i]);
		if (!temp)
			exit_shell(data, 1);
		ret = ft_strjoin(temp, cmd_table->cmd);
		if (!temp)
			free(temp);
		if (!ret)
			exit_shell(data, 1);
		if (access(ret, 0) == 0)
		{
			temp = cmd_table->cmd;
			cmd_table->cmd = ret;
			free(temp);
			return (0);
		}
		free(ret);
		i++;
	}
	printf("minishell: %s: command not found\n", cmd_table->cmd);
	return (1);
}
void	execute_command(t_data *data, t_cmd_table *cmd_table)
{
	pid_t	process1;

	if (find_executable(data, &data->cmdt[0]) == 1)
		return ;
	process1 = fork();
	if (process1 < 0)
		exit_shell(data, 1);
	if (!process1)
	{
		if (execve(data->cmdt[0].cmd, data->cmdt[0].args, data->envp) == -1)
		{
			ft_putstr_fd("minishell : ", 2);
			ft_putstr_fd(data->cmdt[0].cmd, 2);
			perror(" ");
			clean_stuff(data);
			exit(1);
			// here the custom handler for "permission denied"
		}
	}
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
		return (exit2(data, cmd_table));
	return (1);
}

void	executor(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cmdt_count)
	{
		if (execute_builtin(data, &data->cmdt[i]) == 0)
			continue ;
		execute_command(data, &data->cmdt[i]);
	}
	wait(NULL);
}
