/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:41:27 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/21 21:06:44 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(t_data *data, int i)
{
	char	**ret;
	char	*find;

	while (data->envp[++i])
	{
		find = ft_strstr(data->envp[i], "PATH=");
		if (find != NULL)
			break ;
	}
	if (data->envp[i] == NULL)
		exit_shell(data, 1, NULL);
	ret = ft_split(find, ':');
	if (!ret)
		exit_shell(data, 1, NULL);
	i = -1;
	while (ret[++i])
	{
		ret[i] = ft_strjoin(ret[i], "/");
		if (!ret[i])
			(free_double_p(ret), exit_shell(data, 1, NULL));
	}
	return (ret);
}

void	data_init(t_data *data, char **envp)
{
	data->envp = envp;
	data->path = NULL;
	data->input = NULL;
	data->token_max_count = 0;
	data->token_count = 0;
	data->tokens = ft_calloc(20, sizeof(t_token));
	if (!data->tokens)
		exit_shell(data, 1, NULL);
	data->path = get_path(data, -1);
}
