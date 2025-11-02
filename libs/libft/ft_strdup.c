/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:05:00 by rheidary          #+#    #+#             */
/*   Updated: 2025/11/02 16:33:54 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dup_str;
	char	*s_cast;

	dup_str = ft_calloc(1, (ft_strlen(s) + 1));
	s_cast = (char *)s;
	dup_str = ft_strcpy(dup_str, s_cast);
	return (dup_str);
}
//
// int main()
// {
// 	const char	*teststring = "This is a test";
// 	char	*result = ft_strdup(teststring);
// 	char	*resultl = strdup(teststring);
// 	printf("%s\n", result);
// 	printf("%s\n", resultl);
// 	return 0;
// }		TESTED AND WORKS + NORM COMPLIANT