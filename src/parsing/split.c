/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:43:26 by rheidary          #+#    #+#             */
/*   Updated: 2026/02/02 19:58:01 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	handle_quote(char *str, int *len)
{
	char	delim;

	delim = str[*len];
	(*len)++;
	while (str[*len] && str[*len] != delim)
		(*len)++;
	if (str[*len] == delim)
		(*len)++;
}

int	is_delim(char *str)
{
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		return (2);
	if (str[0] == '<' || str[0] == '>' || str[0] == '|' || is_ifs(str[0]))
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
	{
		if (str[len] == '"' || str[len] == '\'')
			handle_quote(str, &len);
		else
			len++;
	}
	return (len);
}

int	count_tokens(char *str)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (is_ifs(str[i]))
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

	if (dst == NULL)
		return (i);
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
	arr = (char **)arena_push(shell->arena, 8 * (tokens + 1), 0, shell);
	if (!arr)
		return (NULL);
	while (i < tokens)
	{
		while (is_ifs(shell->line[j]))
			j++;
		len = token_len(&(shell->line[j]));
		arr[i] = (char *)arena_push(shell->arena, len + 1, 0, shell);
		if (!arr[i])
			return (NULL);
		ft_strlcpy(arr[i], &(shell->line[j]), len + 1);
		j += len;
		i++;
	}
	arr[tokens] = NULL;
	return (arr);
}

// int	main(void)
// {
// 	t_shell *idk = calloc(sizeof(t_shell), 1);
// 	idk->arena = arena_create(1000);
// 	idk->line = "echo -n test1\t\ttest2";
// 	char	**str = split(idk);

// 	for (int i = 0; str[i]; i++)
// 		printf("[%s]\n", str[i]);
// 	return (0);
// }
