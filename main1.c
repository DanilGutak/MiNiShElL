/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:33:07 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/07 13:40:19 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* entry point, initiates data, reads the input,
	lexer-extender-parser-executor-cleaner(repeated) */
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("Error: too many arguments\n", 2));
	data_init(&data, envp);
	while (1)
	{
		mode(&data, INTERACTIVE);
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
		mode(&data, NON_INTERACTIVE);
		if (g_signal == 1 && g_signal--)
			data.exit_code = 130;
		if (!data.input)
			builtin_exit(&data, NULL);
		/* if (data.input[0] != '\0')
			add_history(data.input); */
		data.path = get_path(&data, -1);
		if (data.path && lexer(&data) == 0
			&& expander(&data) == 0 && parser(&data) == 0)
			executor(&data);
		clean_stuff(&data);
	}
}
