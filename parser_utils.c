/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:04:39 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/25 20:13:03 by dgutak           ###   ########.fr       */
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
