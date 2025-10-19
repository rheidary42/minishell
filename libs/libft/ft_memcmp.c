/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:20:01 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 16:11:48 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	int					i;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
//
// int main()
// {
//     char *teststring1 = "This IS a test!";
//     char *teststring2 = "This Is a test!";
//     printf("%d\n", ft_memcmp(teststring1, teststring2, 0));
//     printf("%d\n\n", memcmp(teststring1, teststring2, 0));

//     teststring1 = "";
//     teststring2 = "";
//     printf("%d\n", ft_memcmp(teststring1, teststring2, 14));
//     printf("%d", memcmp(teststring1, teststring2, 14));
//     return 0;
// }
//		TESTED + WORKS AND NORM COMPLAINT