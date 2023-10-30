/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:18:04 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/30 16:05:22 by dgutak           ###   ########.fr       */
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
			ft_free(p[i]);
		ft_free(p);
	}
}

void	free_all(t_data *data)
{
	free_double_p(data->path);
	while (data->token_count--)
	{
		ft_free(data->tokens[data->token_count].value);
		data->tokens[data->token_count].value = NULL;
	}
	ft_free(data->tokens);
	ft_free(data->input);
}


void	exit_shell(t_data *data, int exit_code)
{
	if (exit_code == 1)
		perror("Error");
	clean_stuff(data);
	exit(exit_code);
}
