/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:23:27 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/03 18:19:02 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	is_flag(char *arg)
{
	if (!arg || !*arg || *arg != '-')
		return (1);
	arg++;
	while (*arg)
	{
		if (*arg != 'n')
			return (1);
		arg++;
	}
	return (0);
}

int	builtin_echo(t_data *data, t_cmd_table *cmd_table)
{
	int	new_line;
	int	i;

	new_line = is_flag(cmd_table->args[1]);
	i = ft_tr(new_line, 1, 2);
	while (i < cmd_table->num_args)
	{
		ft_putstr_fd(cmd_table->args[i], STDOUT_FILENO);
		if (i != cmd_table->num_args - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	data->exit_code = 0;
	// (void) data;
	// printf("cmd {%s}\n", cmd_table->cmd);
	// for (int i = 0; cmd_table->args[i]; i++) {
	// 	printf("args %d {%s}\n", i, cmd_table->args[i]);
	// }
	// printf("nbr args {%d}\n", cmd_table->num_args);
	return (FAILURE);
}
