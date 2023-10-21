/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:10:25 by dgutak            #+#    #+#             */
/*   Updated: 2023/06/08 17:18:53 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(const char *str)
{
	int	n;

	n = 0;
	while (str[n] != '\0')
	{
		n++;
	}
	return (n);
}

/* #include <stdio.h>
int main() {
    char *str = "Hell";
    int len = ft_strlen(str);
    printf("The length of the string '%s' is %d\n", str, len);
    return 0;
} */
