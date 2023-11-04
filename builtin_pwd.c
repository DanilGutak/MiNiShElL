/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:39:24 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/04 00:50:12 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* tests only */
void	builtin_pwd(t_data *data, t_cmd_table *cmd_table) // tak ne goditsya
{
	int	position;

	(void) cmd_table;
	data->exit_code = 0;
	position = get_variable_numb(data->envp, "PWD");
	if (position == -1)
		return ; // nu tse bred!
	ft_putendl_fd(data->envp[position] + 4, STDOUT_FILENO);
}
