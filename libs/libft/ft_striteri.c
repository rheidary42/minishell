/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:19:40 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 15:49:19 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
// void	testf(unsigned int i, char *s)
// {
// 	if (i % 2 == 0 && *s != ' ')
// 		*s -= 32;
// }
//
// int main()
// {
// 	char *teststring = strdup("this is not a test");
// 	ft_striteri(teststring, testf);
// 	printf("Test result: %s", teststring);
// 	return (0);
// }		TESTED AND WORKS + NORM COMPLIANT