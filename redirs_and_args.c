/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_and_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:06:06 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/25 19:45:29 by dgutak           ###   ########.fr       */
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

void	fill_redirs(t_data *data, int j, int i)
{
	int	count;

	count = count_redirs(data, i);
	data->cmdt[j].redirs = NULL;
	data->cmdt[j].num_redirs = count;
	if (count <= 0)
		return ;
	data->cmdt[j].redirs = ft_calloc(count, sizeof(t_token));
	if (!data->cmdt[j].redirs)
		exit_shell(data, 1);
	count = 0;
	while (i < data->token_count && data->tokens[i].type != PIPE)
	{
		if (is_not_redir(data->tokens[i].type) == 0)
		{
			data->cmdt[j].redirs[count].type = data->tokens[i].type;
			data->cmdt[j].redirs[count].value = ft_strdup(data->tokens[i++
					+ 1].value);
			if (!data->cmdt[j].redirs[count].value)
				exit_shell(data, 1);
			count++;
		}
		i++;
	}
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
			if (data->cmdt[j].cmd == NULL)
			{
				data->cmdt[j].cmd = ft_strdup(data->tokens[i].value);
				if (!data->cmdt[j].cmd)
					exit_shell(data, 1);
			}
			data->cmdt[j].args[k++] = ft_strdup(data->tokens[i].value);
			if (!data->cmdt[j].args[k - 1])
				exit_shell(data, 1);
		}
	}
	if (data->cmdt[j].cmd != NULL)
		data->cmdt[j].args[k] = NULL;
	return (i);
}
