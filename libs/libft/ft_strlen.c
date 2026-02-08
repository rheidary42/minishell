/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:28:07 by rheidary          #+#    #+#             */
/*   Updated: 2026/02/08 06:13:06 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// int main()
// {
// 	char str[] = "Hello!";
// 	printf("Len of str: %lu\n", ft_strlen(str));
// 	return 0;
// }
//		TESTED AND WORKS + NORM COMPLIANT
