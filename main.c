/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:30:02 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/28 18:32:02 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* clean everything regarding one read of readline(tokens, cmd tables,input, etc..) */
void	clean_stuff(t_data *data)
{
	if (data->tokens)
	{
		while (data->token_count > 0)
		{
			data->token_count--;
			if (data->tokens[data->token_count].value)
				free(data->tokens[data->token_count].value);
		}
		free(data->tokens);
		data->tokens = NULL;
	}
	if (data->cmdt)
	{
		while (data->cmdt_count > 0)
		{
			data->cmdt_count--;
			while (data->cmdt[data->cmdt_count].num_args-- > 0)
				free(data->cmdt[data->cmdt_count]
					.args[data->cmdt[data->cmdt_count].num_args]);
			free(data->cmdt[data->cmdt_count].args);
			while (data->cmdt[data->cmdt_count].num_redirs-- > 0)
				free(data->cmdt[data->cmdt_count]
					.redirs[data->cmdt[data->cmdt_count].num_redirs].value);
			free(data->cmdt[data->cmdt_count].redirs);
			if (data->cmdt[data->cmdt_count].cmd)
				free(data->cmdt[data->cmdt_count].cmd);
		}
		free(data->cmdt);
		data->cmdt = NULL;
	}
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
}
/* entry point, initiates data, reads the input, lexer-extender-parser-executor-cleaner(repeated) */
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("Error: too many arguments\n", 2));
	data_init(&data, envp);
	while (1)
	{
		data.input = readline("minishell$ ");
		if (!data.input)
			builtin_exit(&data, NULL);
		if (data.input[0] != '\0')
			add_history(data.input);
		if (lexer(&data) == 0 && parser(&data) == 0)
			executor(&data);
		clean_stuff(&data);
	}
}
