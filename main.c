/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:33:07 by vfrants           #+#    #+#             */
/*   Updated: 2023/10/30 11:52:41 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

/* clean everything regarding one read of readline(tokens, cmd tables,input, etc..) */
void	clean_stuff(t_data *data)
{
	if (data->tokens)
	{
		while (data->token_count > 0)
			ft_free(data->tokens[--data->token_count].value);
		ft_free(data->tokens);
	}
	if (data->cmdt)
	{
		while (data->cmdt_count > 0)
		{
			data->cmdt_count--;
			while (data->cmdt[data->cmdt_count].num_args-- > 0)
				ft_free(data->cmdt[data->cmdt_count]
					.args[data->cmdt[data->cmdt_count].num_args]);
			ft_free(data->cmdt[data->cmdt_count].args);
			while (data->cmdt[data->cmdt_count].num_redirs-- > 0)
				ft_free(data->cmdt[data->cmdt_count]
					.redirs[data->cmdt[data->cmdt_count].num_redirs].value);
			ft_free(data->cmdt[data->cmdt_count].redirs);
				ft_free(data->cmdt[data->cmdt_count].cmd);
		}
		ft_free(data->cmdt);
	}
	ft_free(data->input);
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
		data.path = get_path(&data, -1);
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
