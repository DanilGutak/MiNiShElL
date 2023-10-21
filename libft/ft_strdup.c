/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:44:46 by dgutak            #+#    #+#             */
/*   Updated: 2023/05/01 09:58:08 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;
	int		size;

	size = 0;
	while (src[size])
		++size;
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* #include <stdio.h>
int main(void)
{
    // Test 1: valid input
    char *src1 = "hello world12312344124";
    char *dest1 = ft_strdup(src1);
    printf("Test 1: src = \"%s\", dest = \"%s\"\n", src1, dest1);
    free(dest1);

    // Test 2: empty string
    char *src2 = "";
    char *dest2 = ft_strdup(src2);
    printf("Test 2: src = \"%s\", dest = \"%s\"\n", src2, dest2);
    free(dest2);

    return 0;
}
 */