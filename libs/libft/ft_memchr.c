/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:19:58 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 16:12:26 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*haystack;
	unsigned char		needle;
	int					i;

	haystack = (const unsigned char *)s;
	needle = (unsigned char)c;
	i = 0;
	while (n--)
	{
		if (haystack[i] == needle)
			return ((void *)haystack + i);
		i++;
	}
	return (NULL);
}

// int main()
// {
//     char *haystack = "Basketball";

//     char needle1 = 'a';
//     printf("ft_memchr: %p\n", ft_memchr(haystack, needle1, 9));
//     printf("memchr: %p\n", memchr(haystack, needle1, 9));

//     char needle2 = '\0';
//     char *res1 = ft_memchr(haystack, needle2, 11);
//     char *res2 = memchr(haystack, needle2, 11);

//     printf("ft_memchr with '\\0':%p, points to: '%c'\n", res1, *res1);
//     printf("memchr with '\\0':%p, points to: '%c'\n", res2, *res2);

//     return 0;
// }
//		TESTED AND WORKS + NORM COMPLIANT