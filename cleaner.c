/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:01:42 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/07 13:46:05 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function `free_cmdt` frees the memory allocated for the `cmdt` structure in the `data` object.
 * 
 * @param data A pointer to a struct of type t_data.
 */
void	free_cmdt(t_data *data)
{
	if (data->cmdt)
	{
		while (data->cmdt_count-- > 0)
		{
			if (data->cmdt[data->cmdt_count].args)
				while (data->cmdt[data->cmdt_count].num_args-- > 0)
					free(data->cmdt[data->cmdt_count].args[data->cmdt[data->cmdt_count].num_args]);
			if (data->cmdt[data->cmdt_count].args)
				free(data->cmdt[data->cmdt_count].args);
			data->cmdt[data->cmdt_count].args = NULL;
			if (data->cmdt[data->cmdt_count].redirs)
				while (data->cmdt[data->cmdt_count].num_redirs-- > 0)
					free(data->cmdt[data->cmdt_count].redirs[data->cmdt[data->cmdt_count].num_redirs].value);
			if (data->cmdt[data->cmdt_count].redirs)
				free(data->cmdt[data->cmdt_count].redirs);
			data->cmdt[data->cmdt_count].redirs = NULL;
			if (data->cmdt[data->cmdt_count].cmd)
				free(data->cmdt[data->cmdt_count].cmd);
			data->cmdt[data->cmdt_count].cmd = NULL;
		}
		free(data->cmdt);
		data->cmdt = NULL;
	}
}

/* clean everything regarding one read of readline(tokens, cmd tables,input,
	etc..) */
/**
 * The function "clean_stuff" frees memory allocated for tokens, command data, input, and path in a
 * struct.
 * 
 * @param data A pointer to a struct called t_data.
 */
void	clean_stuff(t_data *data)
{
	int	i;

	if (data->tokens)
	{
		while (data->token_count > 0)
			free(data->tokens[--data->token_count].value);
		free(data->tokens);
		data->tokens = NULL;
	}
	free_cmdt(data);
	if (data->input)
		free(data->input);
	data->input = NULL;
	i = 0;
	if (data->path)
	{
		while (data->path[i])
			free(data->path[i++]);
		free(data->path);
	}
	data->path = NULL;
}

/**
 * The function "clean_all" frees memory and closes file descriptors in a struct called "data".
 * 
 * @param data The parameter `data` is a pointer to a `t_data` struct.
 */
void	clean_all(t_data *data)
{
	free_double_p(data->envp);
	clean_stuff(data);
	close(data->original_stdout);
	close(data->original_stdin);
}
