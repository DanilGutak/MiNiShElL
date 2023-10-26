/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:09:50 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/26 17:19:12 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_executable(t_data *data, t_cmd_table *cmd_table)
{
	char	*ret;
	char	*temp;
	int		i;

	i = 0;
	if (ft_strchr(cmd_table->cmd, '/') != 0 && access(cmd_table->cmd, F_OK) == 0)
		return (0);
	if (!cmd_table->cmd)
		return (1);
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
void execute_command(t_data *data)
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
			printf("lol\n");
			exit_shell(data, 1);
			//here the custom handler for "permission denied"
		}
	}
}

void	executor(t_data *data)
{
	init_pipes(data);
	execute_command(data);
	wait(NULL);
}
