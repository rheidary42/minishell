/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:39:55 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 15:42:52 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c -32;
	return (c);
}

// int main()
// {
// 	char c = 'a';
// 	printf("%c", ft_toupper(c));
// }
//		TESTED AND WORKS + NORM COMPLIANT