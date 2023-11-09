/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:18:04 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/07 13:36:41 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function `free_double_p` frees the memory allocated for a double pointer and sets all its
 * elements to NULL.
 * 
 * @param p The parameter "p" is a pointer to a pointer to a character (char **).
 */
void	free_double_p(char **p)
{
	int	i;

	i = 0;
	if (p)
	{
		while (p[i])
		{
			free(p[i]);
			p[i] = NULL;
			i++;
		}
		free(p);
		p = NULL;
	}
}

/**
 * The function "free_all" frees all dynamically allocated memory in the "data" structure.
 * 
 * @param data A pointer to a structure of type t_data.
 */
void	free_all(t_data *data)
{
	free_double_p(data->path);
	while (data->token_count--)
	{
		free(data->tokens[data->token_count].value);
		data->tokens[data->token_count].value = NULL;
	}
	free(data->tokens);
	data->tokens = NULL;
	free(data->input);
	data->input = NULL;
}

/**
 * The exit_shell function is used to exit the shell, clean up any resources, and display an error
 * message if necessary.
 * 
 * @param data The parameter `data` is a pointer to a `t_data` struct.
 * @param exit_code The exit_code parameter is an integer that represents the exit status of the shell.
 * It is used to indicate whether the shell is exiting normally or if there was an error. In this code
 * snippet, if the exit_code is 1, it indicates that there was an error and the perror function is
 * called
 */
void	exit_shell(t_data *data, int exit_code)
{
	if (exit_code == 1)
		perror("Error");
	clean_all(data);
	exit(1);
}
