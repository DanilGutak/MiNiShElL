/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:49:24 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/06 15:59:13 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

/**
 * The function "count_args" counts the number of arguments in a given data structure, up until a pipe
 * token is encountered.
 * 
 * @param data A pointer to a struct called "t_data". This struct likely contains information about
 * tokens and their types.
 * @param i The parameter `i` is an integer representing the starting index for counting arguments in
 * the `data->tokens` array.
 * 
 * @return the count of arguments found in the given range of tokens.
 */
int	count_args(t_data *data, int i)
{
	int	count;

	count = 0;
	while (i < data->token_count && data->tokens[i].type != PIPE)
	{
		if (is_arg(data->tokens[i].type) && (i == 0
				|| is_not_redir(data->tokens[i - 1].type)))
			count++;
		i++;
	}
	return (count);
}

/**
 * The function "check_last_heredoc" checks if the last redirection in a command is a heredoc or input
 * redirection.
 * 
 * @param data A pointer to a struct of type t_data.
 * @param j The parameter "j" is an integer that represents the index of a command in the "cmdt" array
 * of the "data" struct.
 */
void	check_last_heredoc(t_data *data, int j)
{
	int	i;

	i = data->cmdt[j].num_redirs;
	while (i--)
	{
		if (data->cmdt[j].redirs[i].type == REDIR_HEREDOC
			|| data->cmdt[j].redirs[i].type == REDIR_IN)
		{
			if (data->cmdt[j].redirs[i].type == REDIR_HEREDOC)
				data->cmdt[j].redirs[i].no_space = 3;
			break ;
		}
	}
}

/**
 * The function `fill_cmdt` initializes the fields of a `cmdt` struct in a `data` struct.
 * 
 * @param data A pointer to a struct of type t_data.
 * @param j The parameter `j` is an integer that represents the index of the `cmdt` array in the `data`
 * structure.
 * @param i The parameter `i` is a pointer to an integer.
 * 
 * @return an integer value.
 */
int	fill_cmdt(t_data *data, int j, int *i)
{
	data->cmdt[j].num_args = count_args(data, *i);
	if (data->cmdt[j].num_args > 0)
	{
		data->cmdt[j].args = ft_calloc((data->cmdt[j].num_args + 1),
				sizeof(char *));
		if (!data->cmdt[j].args)
			return (print_error(data, "ft_calloc error", 1));
	}
	else
		data->cmdt[j].args = NULL;
	data->cmdt[j].cmd = NULL;
	data->cmdt[j].is_child_created = 0;
	data->cmdt[j].pid = 0;
	data->cmdt[j].fd_in = -1;
	data->cmdt[j].fd_out = -1;
	data->cmdt[j].in_file = -1;
	data->cmdt[j].out_file = -1;
	data->cmdt[j].last_heredoc = NULL;
	if (fill_redirs(data, j, *i) == 1)
		return (1);
	check_last_heredoc(data, j);
	*i = fill_cmd_args(data, j, *i - 1) + 1;
	if (*i == 0)
		return (1);
	return (0);
}

/**
 * The function "parser" parses the input data and fills a command table structure.
 * 
 * @param data The parameter `data` is a pointer to a `t_data` struct.
 * 
 * @return an integer value. If `merge_words(data)` returns 1, then the function will return 1.
 * Otherwise, it will return 0.
 */
int	parser(t_data *data)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (merge_words(data) == 1)
		return (1);
	data->cmdt_count = count_pipes(data) + 1;
	data->cmdt = ft_calloc(data->cmdt_count, sizeof(t_cmd_table));
	if (!data->cmdt)
		return (print_error(data, "ft_calloc error", 1));
	while (j < data->cmdt_count)
	{
		if (fill_cmdt(data, j, &i))
			return (1);
		j++;
	}
	return (0);
}
