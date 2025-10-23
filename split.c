/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:43:26 by rheidary          #+#    #+#             */
/*   Updated: 2025/10/23 12:34:33 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	is_delim(char *str)
{
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		return (2);
	if (str[0] == '<' || str[0] == '>' || str[0] == '|' || str[0] == ' ')
		return (1);
	return (0);
}

int	token_len(char *str)
{
	int	len;
	int	d;

	d = is_delim(str);
	len = 0;
	if (d)
		return (d);
	while (str[len] && is_delim(&str[len]) == 0)
		len++;
	return (len);
}

int	count_tokens(char *str)
{
	int	i = 0;
	int	count = 0;
	int	len;

	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		len = token_len(&str[i]);
		count++;
		i += len;
	}
	return (count);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i = 0;

	if (dstsize)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

char	**split(t_shell *shell)
{
	char	**arr;
	int		tokens;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	tokens = count_tokens(shell->line);
	arr = malloc(sizeof(char *) * (tokens + 1));
	if (!arr)
		return (NULL);
	while (i < tokens)
	{
		while (shell->line[j] == ' ')
			j++;
		len = token_len(&shell->line[j]);
		arr[i] = malloc(len + 1);
		if (!arr[i])
			return (NULL);
		ft_strlcpy(arr[i], &shell->line[j], len + 1);
		j += len;
		i++;
	}
	arr[tokens] = NULL;
	return (arr);
}

// int	main(void)
// {
// 	char	**str = split("<< echo hello | wc -l >>> << outfile >>");

// 	for (int i = 0; str[i]; i++)
// 		printf("[%s]\n", str[i]);
// 	for (int i = 0; str[i]; i++)
// 		free(str[i]);
// 	free(str);
// 	return (0);
// }
