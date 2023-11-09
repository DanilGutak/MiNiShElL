/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_and_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:06:06 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/05 21:43:40 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function "count_redirs" counts the number of redirection tokens in a given array of tokens.
 * 
 * @param data A pointer to a struct of type t_data.
 * @param i The parameter `i` is the starting index from where the function should start counting the
 * number of redirections.
 * 
 * @return the count of redirection tokens (tokens that are not pipes) starting from index i in the
 * data->tokens array.
 */
int	count_redirs(t_data *data, int i)
{
	int	count;

	count = 0;
	while (i < data->token_count && data->tokens[i].type != PIPE)
	{
		if (is_not_redir(data->tokens[i].type) == 0)
			count++;
		i++;
	}
	return (count);
}

/**
 * The function `fill_redirs` fills an array of redirections in a data structure with information from
 * a token array.
 * 
 * @param data A pointer to a struct of type t_data.
 * @param j The parameter `j` represents the index of the command in the `cmdt` array of the `data`
 * struct.
 * @param i The parameter `i` is the index of the current token in the `data->tokens` array.
 * 
 * @return an integer value.
 */
int	fill_redirs(t_data *data, int j, int i)
{
	int	count;

	count = count_redirs(data, i);
	data->cmdt[j].redirs = NULL;
	data->cmdt[j].num_redirs = count;
	if (count <= 0)
		return (0);
	data->cmdt[j].redirs = ft_calloc(count, sizeof(t_token));
	if (!data->cmdt[j].redirs)
		return (print_error(data, "ft_calloc", 1));
	count = 0;
	while (i < data->token_count && data->tokens[i].type != PIPE)
	{
		if (is_not_redir(data->tokens[i].type) == 0)
		{
			data->cmdt[j].redirs[count].type = data->tokens[i].type;
			data->cmdt[j].redirs[count].no_space = data->tokens[i].no_space;
			data->cmdt[j].redirs[count].value = ft_strdup(data->tokens[i++
					+ 1].value);
			if (!data->cmdt[j].redirs[count++].value)
				return (print_error(data, "ft_strdup", 1));
		}
		i++;
	}
	return (0);
}

/**
 * The function `fill_cmd_args` fills the command and argument arrays in a data structure based on the
 * tokens provided.
 * 
 * @param data A pointer to a struct of type `t_data`.
 * @param j The variable `j` is used as an index to access elements in the `cmdt` array of the `data`
 * struct. It represents the current command being processed.
 * @param i The variable `i` is used as a loop counter to iterate through the `data->tokens` array. It
 * is passed as a parameter to the `fill_cmd_args` function.
 * 
 * @return the value of the variable 'i'.
 */
int	fill_cmd_args(t_data *data, int j, int i)
{
	int	k;

	k = 0;
	while (++i < data->token_count && data->tokens[i].type != PIPE)
	{
		if (is_arg(data->tokens[i].type) && (i == 0
				|| is_not_redir(data->tokens[i - 1].type)))
		{
			if (data->tokens[i].value[0] == '\0'
				&& data->tokens[i].type == WORD && data->cmdt[j].num_args-- > 0)
				continue ;
			if (data->cmdt[j].cmd == NULL)
			{
				data->cmdt[j].cmd = ft_strdup(data->tokens[i].value);
				if (!data->cmdt[j].cmd)
					return (print_error(data, "ft_strdup", 1) - 2);
			}
			data->cmdt[j].args[k++] = ft_strdup(data->tokens[i].value);
			if (!data->cmdt[j].args[k - 1])
				return (print_error(data, "ft_strdup", 1) - 2);
		}
	}
	if (data->cmdt[j].cmd != NULL)
		data->cmdt[j].args[k] = NULL;
	return (i);
}
