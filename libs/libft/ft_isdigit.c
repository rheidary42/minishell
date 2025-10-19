/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:24:20 by rheidary          #+#    #+#             */
/*   Updated: 2025/04/28 21:21:10 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <ctype.h> //TESTING PURPOSES

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// int main()
// {
// 	unsigned char c = '9';
// 	unsigned int d = 4;
// 	printf("My isdigit: %d\n", ft_isdigit(c));
//  printf("My isdigit 2: %d\n", ft_isdigit(d));
//  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ 
//  RETURN 0, BECAUSE ONLY CHECKS CHAR NOT INT
//  -------------------------------------------
// 	printf("Libc isdigit: %d\n", isdigit(c));
//  printf("Libc isdigit 2: %d\n", isdigit(d));
// 	return (0);
// }
// TESTED AND WORKS + NORM COMPLIANT
