/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:10:06 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 16:11:39 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*destcast;
	unsigned const char	*srccast;
	size_t				i;

	destcast = (unsigned char *)dest;
	srccast = (unsigned const char *)src;
	i = 0;
	if (n == 0)
		return (dest);
	while (n--)
	{
		destcast[i] = srccast[i];
		i++;
	}
	return (dest);
}

// int main()
// {
// 	char *teststring1 = "Copy This";
// 	char testdest1[10];
//
// 	int a = -10;
// 	int b;
//	
// 	ft_memcpy(testdest1, teststring1, 9);
// 	ft_memcpy(&b, &a, sizeof(int) * 2);
//
// 	printf("%s\n", testdest1);
// 	printf("%d", b);
// 	return 0;
// }
//		TESTED AND WORKS + NORM COMPLIANT