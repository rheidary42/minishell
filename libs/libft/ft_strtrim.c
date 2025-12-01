/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <boenkhja@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:35:25 by boenkhja          #+#    #+#             */
/*   Updated: 2025/05/02 17:35:41 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_strlen(const char *s1)
{
	int	i;

	i = 0;
	while (s1[i] != 0)
		i++;
	return (i);
}

static int	check(char c, const char *set)
{
	int		i;

	i = 0;
	while (set[i] != 0)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	end_trim(char *str, const char *set, int end)
{
	while (check(str[end], set) == 1)
		end--;
	return (end + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	char	*hi;
	int		i;
	int		j;
	int		end;

	i = 0;
	j = 0;
	str = (char *)s1;
	hi = NULL;
	if (s1 == NULL)
		return (NULL);
	while (str[i] != 0 && check(str[i], set) == 1)
		i++;
	end = my_strlen(&str[i]);
	if (check(str[end + i - 1], set) == 1 && str[i] != 0)
		end = end_trim(&str[i], set, my_strlen(&str[i]) - 1);
	hi = (char *)malloc((end + 1) * sizeof(char));
	if (hi == NULL)
		return (NULL);
	while (str[i] != 0 && j < end)
		hi[j++] = str[i++];
	hi[j] = '\0';
	return (hi);
}
/*
int	main(void)
{
	char	str[] = " lorem ipsum dolor sit amet";
	char	set[] = "l ";
	printf("res = %s\n", ft_strtrim("   xxx   xxx", " x"));
	return 0;
}*/
