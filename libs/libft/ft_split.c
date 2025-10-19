/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:26:08 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/15 15:51:09 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strcount(char const *s, char c)
{
	int	count;
	int	i;
	int	booli;

	booli = 0;
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && booli == 0)
		{
			booli = 1;
			count++;
		}
		else if (s[i] == c)
			booli = 0;
		i++;
	}
	return (count);
}

size_t	f_sl(const char *s, int start, char c)
{
	while (s[start] != '\0' && s[start] != c)
		(start)++;
	return (start);
}

void	free_mem(char **str_arr, int i)
{
	while (--i >= 0)
		free (str_arr[i]);
	free (str_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**str_arr;
	int		str_count;
	int		i;
	int		j;

	i = -1;
	j = 0;
	str_count = strcount(s, c);
	str_arr = malloc(sizeof (char *) * (str_count + 1));
	if (!str_arr)
		return (NULL);
	str_arr[str_count] = NULL;
	while (s[++i] != '\0')
	{
		if (s[i] == c)
			continue ;
		str_arr[j] = ft_substr(s, i, f_sl(s, i, c) - i);
		if (!str_arr[j])
			return (free_mem(str_arr, j), NULL);
		i = f_sl(s, i, c) - 1;
		j++;
	}
	return (str_arr);
}
// int main()
// {
// 	char const *teststring = "This,is,,,not,,,a,test,!";
// 	char c = ',';
// 	char **testresult = ft_split(teststring, c);
// 	int	b = 0;
// 	int i = 0;
// 	while (testresult[i] != NULL)
// 	{
// 		printf("String #%d: %s\n", i + 1, testresult[i]);
// 		i++;
// 	}
// 	while (testresult[b] != NULL)
// 	{
// 		free(testresult[b++]);
// 	}
// 	free(testresult);
// 	return 0;
// }		TESTED AND WORKS + NORM COMPLIANT