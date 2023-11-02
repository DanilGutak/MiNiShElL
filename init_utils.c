/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:52:16 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/02 14:53:52 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_original_fds(t_data *data)
{
	data->original_stdin = dup(STDIN_FILENO);
	if (data->original_stdin == -1)
		exit_shell(data, 1);
	data->original_stdout = dup(STDOUT_FILENO);
	if (data->original_stdout == -1)
		exit_shell(data, 1);
}
