/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:22:26 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 22:35:30 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_c;
	char const	*src_c;
	size_t		i;

	dest_c = (char *)dest;
	src_c = (const char *)src;
	i = 0;
	if (src_c < dest_c)
	{
		while (n)
		{
			n--;
			dest_c[n] = src_c[n];
		}
	}
	if (dest_c < src_c)
	{
		while (i < n)
		{
			dest_c[i] = src_c[i];
			i++;
		}
	}
	return (dest);
}

// int main()
// {
// 	char sResult[] = {67, 68, 67, 68, 69, 0, 45};
// 	printf("%s\n", (char*)ft_memmove(sResult + 1, sResult, 2));
// 	char sResult2[] = {67, 68, 67, 68, 69, 0, 45};
// 	printf("%s\n", (char*)memmove(sResult2 + 1, sResult2, 2));
// 	return 0;
// }
// 		TESTED AND WORKS + NORM COMPLIANT