/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:23:27 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/03 14:53:10 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	builtin_echo(t_data *data, t_cmd_table *cmd_table)
{
	(void) data;
	printf("cmd %s\n", cmd_table->cmd);
	for (int i = 0; cmd_table->args[i]; i++) {
		printf("args %s\n", cmd_table->args[i]);
	}
	printf("nbr args %d\n", cmd_table->num_args);
	return (1);
}
