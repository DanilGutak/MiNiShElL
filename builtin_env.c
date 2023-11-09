/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:33:32 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/03 19:47:41 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The `builtin_env` function prints the environment variables to the standard output.
 * 
 * @param data A pointer to a structure of type t_data, which contains information about the program's
 * environment.
 * @param cmd_table A pointer to a structure that represents a command table. It is not used in this
 * function and is therefore ignored.
 */
void	builtin_env(t_data *data, t_cmd_table *cmd_table)
{
	int	i;

	(void) cmd_table;
	data->exit_code = 0;
	i = 0;
	while (data->envp[i])
	{
		ft_putendl_fd(data->envp[i], STDOUT_FILENO);
		i++;
	}
}
