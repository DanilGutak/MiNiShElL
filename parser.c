/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:49:24 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/06 14:21:22 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

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

/* transforms tokens into cmd tables.
merges words with no_spaces
create cmd table for each pipe
fill cmd, args and redirs in cmd table
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
	if (fill_redirs(data, j, *i) == 1)
		return (1);
	*i = fill_cmd_args(data, j, *i - 1) + 1;
	if (*i == 0)
		return (1);
	return (0);
}

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
