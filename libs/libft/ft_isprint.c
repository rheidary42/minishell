/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:18:58 by rheidary          #+#    #+#             */
/*   Updated: 2025/04/29 22:16:04 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}
// int main()
// {
// 	char c = -22;
// 	printf("%d", ft_isprint(c));
// 	return (0);
// }
// TESTED AND WORKS + NORM COMPLIANT
