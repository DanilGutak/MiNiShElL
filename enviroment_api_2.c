/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_api_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:43:19 by vfrants           #+#    #+#             */
/*   Updated: 2023/10/30 18:46:49 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* delete a variable from the envp */
int	delete_variable(t_data *data, char *key)
{
	char	**new;
	char	position;
	int		size;
	int		i;

	position = get_variable_numb(data->envp, key);
	if (position == -1)
		return (FAILURE);
	size = ft_len_split(data->envp);
	new = (char **)ft_calloc(sizeof (char *), size);
	if (!new)
		return (MALLOC_F); // same error here related to malloc
	i = 0;
	while (i < size)
	{
		new[i] = data->envp[ft_tr(i < position, i, i + 1)];
		i++;
	}
	ft_free(data->envp);
	data->envp = new;
	return (SUCCESS);
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
int	create_variable(t_data *data, char *key, char *value)
{
	char	**new;
	char	*buffer;
	char	*new_one;
	int		size;
	int		i;

	buffer = ft_strcat(key, "=");
	if (buffer == NULL)
		return (MALLOC_F);
	new_one = ft_strcat(buffer, value);
	ft_free(buffer);
	if (new_one == NULL)
		return (MALLOC_F);
	size = ft_len_split(data->envp);
	new = (char **)ft_calloc(sizeof (char *), size + 2);
	if (new == NULL)
		return (MALLOC_F);
	i = -1;
	while (++i < size)
		new[i] = data->envp[i];
	new[i++] = new_one;
	new[i] = NULL;
	ft_free(data->envp);
	data->envp = new;
	return (SUCCESS);
}

/* += operator for the variables. key in format 'VAL'. IDK IF WE NEED IT*/
int	append_variable(t_data *data, char *key, char *value)
{
	char	*new;
	char	*temp;
	int		position;

	position = get_variable_numb(data->envp, key);
	if (position == -1)
		return (create_variable(data, key, value));
	temp = ft_strcat(data->envp[position], "=");
	if (temp == NULL)
		return (MALLOC_F);
	new = ft_strcat(temp, value);
	if (new == NULL)
		return (MALLOC_F);
	ft_free(data->envp[position]);
	data->envp[position] = new;
	return (SUCCESS);
}
