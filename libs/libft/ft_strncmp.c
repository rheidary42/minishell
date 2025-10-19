/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:27:14 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 17:14:34 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
//
// int main()
// {
// 	size_t	i = 0;
// 	const char *teststring1 = "HelLo ";
// 	const char *teststring2 = "Hello";
// 	int testresult = ft_strncmp(teststring1, teststring2, i);
// 	printf("%d", testresult);
// }		TESTED AND WORKS + NORM COMPLIANT