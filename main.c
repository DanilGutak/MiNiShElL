/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:33:07 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/03 12:26:04 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

/* clean everything regarding one read of readline(tokens, cmd tables,input,
	etc..) */
void	clean_stuff(t_data	*data)
{
	if (data->tokens)
	{
		while (data->token_count > 0)
			free(data->tokens[--data->token_count].value);
		free(data->tokens);
		data->tokens = NULL;
	}
	if (data->cmdt)
	{
		while (data->cmdt_count > 0)
		{
			data->cmdt_count--;
			while (data->cmdt[data->cmdt_count].num_args-- > 0)
				free(data->cmdt[data->cmdt_count].args[data->cmdt[data->cmdt_count].num_args]);
			free(data->cmdt[data->cmdt_count].args);
			data->cmdt[data->cmdt_count].args = NULL;
			while (data->cmdt[data->cmdt_count].num_redirs-- > 0)
				free(data->cmdt[data->cmdt_count].redirs[data->cmdt[data->cmdt_count].num_redirs].value);
			free(data->cmdt[data->cmdt_count].redirs);
			data->cmdt[data->cmdt_count].redirs = NULL;
			free(data->cmdt[data->cmdt_count].cmd);
			data->cmdt[data->cmdt_count].cmd = NULL;
		}
		free(data->cmdt);
		data->cmdt = NULL;
	}
	free(data->input);
	data->input = NULL;
	free_double_p(data->path);
	data->path = NULL;
}
void clean_all(t_data *data)
{
	free_double_p(data->envp);
	clean_stuff(data);
	close(data->original_stdout);
	close(data->original_stdin);
}
/* entry point, initiates data, reads the input,
	lexer-extender-parser-executor-cleaner(repeated) */
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("Error: too many arguments\n", 2));
	data_init(&data, envp);
	while (1)
	{
		data.path = get_path(&data, -1);
		data.input = readline("minishell$ ");
		if (!data.input)
			builtin_exit(&data, NULL);
		if (data.input[0] != '\0')
			add_history(data.input);
		if (lexer(&data) == 0 && expander(&data) == 0 && parser(&data) == 0)
		{
			executor(&data);
		}
		//printf("exit code: %d\n", data.exit_code);
		clean_stuff(&data);
	}
}
