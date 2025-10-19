/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:05:15 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/17 15:21:00 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;

	i = 0;
	if (!s || start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substring = malloc((sizeof(char) * (len + 1)));
	if (!substring)
		return (NULL);
	while (len--)
	{
		substring[i] = s[start];
		i++;
		start++;
	}
	substring[i] = '\0';
	return (substring);
}
//
// int main()
// {
//     char *teststring = "This is not a test";
//     char *testresult = ft_substr(teststring, 5, 6);
//     printf("Test result: %s\n", testresult);
//     return 0;
// }    TESTED AND WORKS + NORM COMPLIANT