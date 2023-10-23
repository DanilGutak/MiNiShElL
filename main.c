/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:30:02 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/23 17:44:03 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			exit2(&data, errno);
		if (data.input[0] != '\0')
			add_history(data.input);
		if (lexer(&data) == 0 && parser(&data) == 0)
		{
			free(data.input);
			continue ;
		}
		else
			free(data.input);
	}
	return (0);
}
