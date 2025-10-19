/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:05:21 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/26 13:48:25 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_comb;
	int		a;
	int		b;

	str_comb = malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str_comb)
		return (NULL);
	a = 0;
	b = 0;
	while (s1[a] != '\0')
	{
		str_comb[a] = s1[a];
		a++;
	}
	while (s2[b] != '\0')
	{
		str_comb[a] = s2[b];
		a++;
		b++;
	}
	str_comb[a] = '\0';
	return (str_comb);
}

// int main()
// {
// 	char *testpre = "This is";
// 	char *testsuf = " not a test";
// 	char *testresult = ft_strjoin(testpre, testsuf);
// 	printf("Test result: %s\n", testresult);
// 	printf("Null term check: %d\n", testresult[18]); DOESNT WORK
// 	return 0;
// }