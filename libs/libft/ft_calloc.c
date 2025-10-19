/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:23:36 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 23:46:50 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total;

	total = nmemb * size;
	if (!nmemb || !size)
		return (malloc(0));
	if (total / size != nmemb)
		return (NULL);
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}

// int main()
// {
//     char *twod_arr = ft_calloc(2, 4);
//     char *twod_arrl = calloc(2, 4);
//     twod_arr[7] = 'L'; 
//     twod_arrl[7] = 'L';
//     // NULL test
//     printf("My Calloc Test:   %d\n", twod_arr[6]);
//     printf("Libc Calloc Test: %d\n", twod_arrl[6]);
//     // init test
//     printf("My Calloc Test:   %c\n", twod_arr[7]);
//     printf("Libc Calloc Test: %c\n", twod_arrl[7]);
//     return (0);
// }	TESTED + WORKS AND NORM COMPLIANT
