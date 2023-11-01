/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:40:09 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/01 21:36:50 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long int number)
{
	int	count;

	count = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		number = -number;
		count++;
	}
	while (number != 0)
	{
		number /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*ret;
	long int	nbr;
	int			flag;

	nbr = n;
	flag = 0;
	n = count_digits(nbr);
	ret = ft_calloc(sizeof(char), (size_t)(n + 1));
	if (!ret)
		return (0);
	if (nbr < 0)
	{
		ret[0] = '-';
		nbr = -nbr;
		flag = 1;
	}
	ret[n] = '\0';
	while (--n >= flag)
	{
		ret[n] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (ret);
}

/* #include <stdio.h>

int	main(void)
{
	char *kek = ft_itoa(-1022131234);
	printf("%s", kek);
} */
