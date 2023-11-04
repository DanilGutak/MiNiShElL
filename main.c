/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:33:07 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/04 01:42:00 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	handler(int status)
{
	printf("SIGNAL IS RECEIVED ---%d---", status);
	if (status == SIGINT)
		g_signal = CNTRL_C;
	else if (status == SIGQUIT)
		g_signal = CNTRL_S;
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
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
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
		clean_stuff(&data);
	}
}
