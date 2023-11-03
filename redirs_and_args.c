/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_and_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:06:06 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/03 18:32:52 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			data->cmdt[j].redirs[count].value = ft_strdup(data->tokens[i++
					+ 1].value);
			if (!data->cmdt[j].redirs[count].value)
				return (print_error(data, "ft_strdup", 1));
			count++;
		}
		i++;
	}
	return (0);
}

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
