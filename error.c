/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:51:04 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/21 20:57:56 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void syntax_error(t_data *data, char *msg)
{
    ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
     ft_putstr_fd("`", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("'\n", 2);
    free_all(data);
    exit(2);
}