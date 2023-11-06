/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:04:39 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/06 14:07:17 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_arg(t_token_type type)
{
	if (type == WORD || type == DQUOTE || type == SQUOTE)
		return (1);
	return (0);
}

int	is_not_redir(t_token_type type)
{
	if (type == WORD || type == SQUOTE || type == DQUOTE || type == PIPE)
		return (1);
	return (0);
}

int	count_pipes(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < data->token_count)
		if (data->tokens[i].type == PIPE)
			j++;
	return (j);
}

int	count_new_tokens(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < data->token_count)
	{
		if (data->tokens[i].type == WORD)
		{
			j = 0;
			while (data->tokens[i].value[j])
			{
				if (data->tokens[i].value[j] == ' ')
					k++;
				j++;
			}
		}
		k++;
		i++;
	}
	return (k);
}
