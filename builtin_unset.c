/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:44:45 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/06 18:10:50 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Builtin unset:
	always exit with exit 0, as original one does (bash)
	unlink or ignore the variable
*/
void	builtin_unset(t_data *data, t_cmd_table *cmd_table)
{
	int	i;

	i = 1;
	data->exit_code = 0;
	if (data->cmdt_count != 1)
		return ;
	while (i < cmd_table->num_args)
	{
		if (delete_variable(data, cmd_table->args[i]) == MALLOC_F)
		{
			print_error(data, "Malloc failed", 1);
			return ;
		}
		i++;
	}
}
