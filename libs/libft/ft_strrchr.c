/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:19:49 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 18:49:57 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = ft_strlen(s);
	if ((char)c == '\0')
		return (&str[i]);
	while (i > 0)
	{
		i--;
		if (str[i] == (char)c)
			return (&str[i]);
	}
	return (NULL);
}
//  int main()
// {
// char *haystack = "tripouille";
// char needle = 't';
// char	*test = calloc(1, 1);
// test = strdup("hello");
// printf("%s\n", strrchr(test, 'V')); //strrchr(haystack, needle));
// printf("%s", ft_strrchr(test, 'V'));// ft_strrchr(haystack, needle));
// return 0;
// } 
//		TESTED AND WORKS + NORM COMPLIANT