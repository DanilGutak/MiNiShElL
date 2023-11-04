/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:33:07 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/04 18:45:41 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		mode(&data, INTERACTIVE);
		data.path = get_path(&data, -1);
		data.input = readline("minishell$ ");
		if (!data.input)
			builtin_exit(&data, NULL);
		if (data.input[0] != '\0')
			add_history(data.input);
		if (lexer(&data) == 0 && expander(&data) == 0 && parser(&data) == 0)
		{
			mode(&data, NON_INTERACTIVE);
			executor(&data);
		}
		clean_stuff(&data);
	}
}/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char *line;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("Error: too many arguments\n", 2));
	data_init(&data, envp);
	while (1)
	{
		setup_signals(&data);
		data.path = get_path(&data, -1);
		if (isatty(0))
			data.input = readline("minishell$ ");
		else
		{
			line = get_next_line(0, 0);
			if (!line)
				builtin_exit(&data, NULL);
			data.input = ft_strtrim(line, "\n");
			free(line);
		}
		if (!data.input)
			builtin_exit(&data, NULL);
		if (data.input[0] != '\0')
			add_history(data.input);
		if (lexer(&data) == 0 && expander(&data) == 0 && parser(&data) == 0)
		{
			executor(&data);
		}
		clean_stuff(&data);
	}
} */
