/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:36:06 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 22:41:28 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char const *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i + 1 < size)
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
	{
		dest[i] = '\0';
	}
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}
/*
#include <bsd/string.h>
int	main()
{
	char testsrc[] = "coucou";
	char *testdest = malloc(20);
	testdest = memset(testdest, 'A', 10);
	printf("%s\n", testdest);
	printf("%zu\n", ft_strlcpy(testdest, testsrc, 0));
	printf("%s\n", testdest);
	printf("%zu\n", strlcpy(testdest, testsrc, 0));
	printf("%s\n", testdest);
	return 0;
}*/
//		TESTED AND WORKS + NORM COMPLIANT
