/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:39:24 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/05 13:31:06 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* tests only */
/**
 * The function `builtin_pwd` prints the current working directory.
 * 
 * @param data The parameter "data" is a pointer to a structure of type "t_data". This structure likely
 * contains information and variables related to the current state of the program or shell.
 */
void	builtin_pwd(t_data *data)
{
	char	*temp;

	data->exit_code = 0;
	temp = getcwd(NULL, 0);
	if (temp)
		printf("%s\n", temp);
	free(temp);
}
