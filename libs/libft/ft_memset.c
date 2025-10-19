/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:17:10 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 15:57:27 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

// int main()
// {
// 	char c = 'a';
// 	char *ptr = "Test123";
// 	size_t n = 22;
// 	ptr = malloc(7);
// 	ft_memset(ptr, c, n);
// 	printf("%s", ptr);
// 	return (0);
// }
//		TESTED AND WORKS + NORM COMPLIANT