/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:39:26 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 17:43:40 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char const *src, size_t size)
{
	unsigned int	j;
	unsigned int	dest_l_stor;
	unsigned int	src_l_stor;

	j = 0;
	dest_l_stor = 0;
	src_l_stor = 0;
	while (dest[dest_l_stor] != '\0')
	{
		dest_l_stor++;
	}
	while (src[src_l_stor] != '\0')
	{
		src_l_stor++;
	}
	if (size <= dest_l_stor)
		return (src_l_stor + size);
	while (src[j] != 0 && dest_l_stor + j < size - 1)
	{
		dest[dest_l_stor + j] = src[j];
		j++;
	}
	dest[dest_l_stor + j] = '\0';
	return (dest_l_stor + src_l_stor);
}

//	NOT TESTED