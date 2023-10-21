/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:17:02 by dgutak            #+#    #+#             */
/*   Updated: 2023/04/25 17:12:43 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (*s1 && (*s1 == *s2) && i < n)
	{
		s1++;
		s2++;
		i++;
	}
	if (i == n)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/*  #include <stdio.h>

int main(void) {
    char s1[] = "helao";
    char s2[] = "helbo";
    int result = ft_strncmp(s1, s2, 3);
    printf("Test case 1: %d\n", result);

    char s3[] = "world";
    char s4[] = "hello";
    result = ft_strncmp(s3, s4, 3);
    printf("Test case 2: %d\n", result);

    char s5[] = "hello";
    char s6[] = "world";
    result = ft_strncmp(s5, s6, 3);
    printf("Test case 3: %d\n", result);

    return 0;
}  */