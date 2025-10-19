/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:37:34 by rheidary          #+#    #+#             */
/*   Updated: 2025/05/17 14:55:41 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char s, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (s == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	find_end(char const *s1, char const *set)
{
	int	count;
	int	length;

	count = 0;
	length = ft_strlen (s1) - 1;
	while (is_set(s1[length], set) == 1 && length >= 0)
	{
		length--;
		count++;
	}
	return (count);
}

static int	find_start(char const *s1, char const *set)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (is_set(s1[i], set) == 1)
	{
		i++;
		count++;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*redu_str;
	int		end;
	int		start;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s1);
	end = find_end(s1, set);
	start = find_start(s1, set);
	end = j - (end + start);
	if (end < 0)
		end = 0;
	redu_str = ft_calloc(sizeof (char), end + 1);
	if (!redu_str)
		return (NULL);
	while (i < end)
	{
		redu_str[i] = s1[start];
		i++;
		start++;
	}
	redu_str[i] = '\0';
	return (redu_str);
}
// int main()
// {
// 	char * s = ft_strtrim("   xxx   xxx", " x");
// 	printf("%s\n", s);
// 	free(s);
// 	return 0;
// }
// int main()
// {
// 	char *teststring = "Basketball";
// 	char *testset = "Bal";
// 	char *testresult = ft_strtrim(teststring, testset);

// 	printf("Test result: %s", testresult);
// 	return (0);
// }
//			TESTED AND WORKS + NORM COMPLIANT