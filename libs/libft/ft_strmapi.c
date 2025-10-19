/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 03:55:31 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 15:46:36 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	char				*final_str;

	i = 0;
	final_str = malloc(sizeof (char) * (ft_strlen(s) + 1));
	if (!final_str)
		return (NULL);
	while (s[i] != '\0')
	{
		final_str[i] = f(i, s[i]);
		i++;
	}
	final_str[i] = '\0';
	return (final_str);
}
// char	testf(unsigned int i, char c)
// {
// 	if (c == ' ')
// 		return (' ');
// 	if (i % 2 == 0)
// 		c -= 32;
// 	return (c);
// }
//
// int main()
// {
// 	char *teststring = "this is not a test";
// 	char *testresult = ft_strmapi(teststring, testf);
// 	printf("Test result: %s", testresult);
// 	return (0);
// }		TESTED AND WORKS + NORM COMPLIANT