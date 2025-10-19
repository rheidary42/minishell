/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:30:46 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 15:50:51 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	a;

	i = 0;
	a = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == a)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + ft_strlen(s));
	return (NULL);
}
//
// int main()
// {
// 	char *haystack = "asketball";

//     // Test normal char
//     char needle1 = 'a';
//     printf("ft_strchr: %s\n", ft_strchr(haystack, needle1));
//     printf("strchr: %s\n", strchr(haystack, needle1));

// 	// Test '\0'
//     char needle2 = '\0';
//     char *res1 = ft_strchr(haystack, needle2);
// 	char *res2 = strchr(haystack, needle2);

// 	printf("ft_strchr with '\\0': %p, points to: '%s'\n", (void *)res1, res1);
// 	printf("strchr with '\\0': %p, points to: '%s'\n", (void *)res2, res2);

// 	return 0;
// }
//		TESTED AND WORKS + NORM COMPLIANT
