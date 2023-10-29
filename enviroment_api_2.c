/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_api_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:43:19 by vfrants           #+#    #+#             */
/*   Updated: 2023/10/29 16:03:11 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* += operator for the variables. key in format 'VAL' */
int	append_variable(char **envp, char *key, char *value)
{
	char	*new;
	int		position;

	position = get_variable_numb(envp, key);
	if (position == -1)
		return (FAILURE);
	new = ft_strcat(envp[position], value);
	if (new == NULL)
		return (FAILURE); // should exit intead of return NULL
	ft_free(envp[position]);
	envp[position] = new;
	return (SUCCESS);
}

/* delete a variable from the envp */
void	delete_variable(t_data *data, char *key)
{
	char	**new;
	char	position;
	int		size;
	int		i;

	position = get_variable_numb(data->envp, key);
	if (position == -1)
		return ;
	size = ft_len_split(data->envp);
	new = (char **)ft_calloc(sizeof (char *), size);
	if (!new)
		exit_shell(data, 1); // same error here related to malloc
	i = 0;
	while (i < size)
	{
		new[i] = data->envp[ft_tr(i < position, i, i + 1)];
		i++;
	}
	ft_free(data->envp);
	data->envp = new;
}

int	is_valid_key(char *key)
{
	if (key == NULL || !(ft_isalpha(*key) || *key == '_'))
		return (0);
	while (*key)
	{
		if (!(ft_isalnum(*key) || *key == '_'))
			return (0);
		key++;
	}
	return (1);
}

/* should add one more variable to the environment.
 kinda confused about the time when you print errors */
void	create_variable(t_data *data, char *key, char *value)
{
	char	**new;
	char	*new_one;
	int		size;
	int		i;

	new_one = ft_strcat(key, value);
	if (new_one == NULL)
		exit_shell(data, 1); // probably need to put  error message later
	size = ft_len_split(data->envp);
	new = (char **)ft_calloc(sizeof (char *), size + 2);
	if (new == NULL)
		exit_shell(data, 1); // same here, sm text for error
	i = 0;
	while (i < size)
	{
		new[i] = data->envp[i];
		i++;
	}
	new[i++] = new_one;
	new[i] = NULL;
	ft_free(data->envp); // free only **, the strings within are still needed
	data->envp = new;
}
