/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:39:39 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 22:38:42 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen((char *) little);
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i + little_len <= len)
	{
		n = 0;
		while (big[i + n] == little[n] && (i + n) < len)
		{
			n++;
			if (n == little_len)
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	char * empty = (char*)"";
// 	printf("%s", ft_strnstr(empty, "", 0));
// 	return 0;
// }
// int main()
// {
// 	char *haystack = "Basketball ball";
// 	char *needle1 = "";
// 	char *needle2 = "Volley";
// 	char *needle3 = "ball";
// 	size_t	i = 11;

// // No strnstr in libc
// // TEST CASE 1: LITTLE EMPTY
// 	char *result1 = ft_strnstr(haystack, needle1, i);
// 	printf("Test Case 1  ft; Little empty returns: %s\n", result1);  
// // TEST CASE 2: NO OCCURANCE OF LITTLE
// 	char *result2 = ft_strnstr(haystack, needle2, 11);
// 	printf("Test Case 2  ft; Litle not found returns: %s\n", result2);
// // TEST CASE 3: LITTLE FOUND IN BIG
// 	char *result3 = ft_strnstr(haystack, needle3, 11);
// 	printf("Test Case 3  ft; Little found in big returns: %s\n", result3);
// 	return 0;
// }
//		TESTED + WORKS AND NORM COMPLIANT