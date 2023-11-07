/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:18:04 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/07 13:36:41 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_p(char **p)
{
	int	i;

	i = 0;
	if (p)
	{
		while (p[i])
		{
			free(p[i]);
			p[i] = NULL;
			i++;
		}
		free(p);
		p = NULL;
	}
}

void	free_all(t_data *data)
{
	free_double_p(data->path);
	while (data->token_count--)
	{
		free(data->tokens[data->token_count].value);
		data->tokens[data->token_count].value = NULL;
	}
	free(data->tokens);
	data->tokens = NULL;
	free(data->input);
	data->input = NULL;
}

void	exit_shell(t_data *data, int exit_code)
{
	if (exit_code == 1)
		perror("Error");
	clean_all(data);
	exit(1);
}
