/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:51:36 by rheidary          #+#    #+#             */
/*   Updated: 2025/04/28 21:12:41 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

// int main()
// {
// 	unsigned char c = 'a';
// 	unsigned int i = 1;
// 	unsigned char d = 'D';
// 	unsigned int j = 42;
// 	printf("%d\n", ft_isalpha(c));
// 	printf("%d\n", ft_isalpha(i));
// 	printf("%d\n", ft_isalpha(d));
// 	printf("%d\n", ft_isalpha(j));
// 	return 0;
// }
// TESTED AND WORKS + NORM COMPLIANT 
