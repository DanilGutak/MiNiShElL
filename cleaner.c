/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:01:42 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/03 17:01:52 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmdt(t_data *data)
{
	if (data->cmdt)
	{
		while (data->cmdt_count > 0)
		{
			data->cmdt_count--;
			while (data->cmdt[data->cmdt_count].num_args-- > 0)
				free(data->cmdt[data->cmdt_count]
					.args[data->cmdt[data->cmdt_count].num_args]);
			free(data->cmdt[data->cmdt_count].args);
			data->cmdt[data->cmdt_count].args = NULL;
			while (data->cmdt[data->cmdt_count].num_redirs-- > 0)
				free(data->cmdt[data->cmdt_count]
					.redirs[data->cmdt[data->cmdt_count].num_redirs].value);
			free(data->cmdt[data->cmdt_count].redirs);
			data->cmdt[data->cmdt_count].redirs = NULL;
			free(data->cmdt[data->cmdt_count].cmd);
			data->cmdt[data->cmdt_count].cmd = NULL;
		}
		free(data->cmdt);
		data->cmdt = NULL;
	}
}

/* clean everything regarding one read of readline(tokens, cmd tables,input,
	etc..) */
void	clean_stuff(t_data *data)
{
	if (data->tokens)
	{
		while (data->token_count > 0)
			free(data->tokens[--data->token_count].value);
		free(data->tokens);
		data->tokens = NULL;
	}
	free_cmdt(data);
	free(data->input);
	data->input = NULL;
	free_double_p(data->path);
	data->path = NULL;
}

void	clean_all(t_data *data)
{
	free_double_p(data->envp);
	clean_stuff(data);
	close(data->original_stdout);
	close(data->original_stdin);
}