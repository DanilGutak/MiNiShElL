/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:18:04 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/21 21:02:55 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_p(char **p)
{
	int	i;

	i = -1;
	if (p)
	{
		while (p[++i])
			free(p[i]);
		free(p);
	}
}

void	free_all(t_data *data)
{
	free_double_p(data->path);
	if (data->input)
		free(data->input);
}

void	exit_shell(t_data *data, int exit_code, char *temp)
{
	if (exit_code == 1)
		perror("Error");
	if (exit_code == 2)
		syntax_error(data, temp);
	free_all(data);
	exit(exit_code);
}
