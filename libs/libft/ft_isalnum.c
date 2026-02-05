/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:53:45 by rheidary          #+#    #+#             */
/*   Updated: 2026/02/05 14:15:35 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

// int main()
// {
// 	unsigned char c = 'T';
// 	unsigned char e = '9';
// 	unsigned int d = 4;
// 	printf("My Alnum > %d\n", ft_isalnum(c));
// 	printf("My Alnum > %d\n", ft_isalnum(e));
// 	printf("My Alnum > %d\n", ft_isalnum(d));
// 	printf("Libc Alnum > %d\n", isalnum(c));
// 	printf("Libc Alnum > %d\n", isalnum(e));
// 	printf("Libc Alnum > %d\n", isalnum(d));
// 	return (0);
// }
// TESTED AND WORKS + NORM COMPLIANT