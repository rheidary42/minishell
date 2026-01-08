/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <boenkhja@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:59:03 by boenkhja          #+#    #+#             */
/*   Updated: 2025/05/21 02:59:04 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	my_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	newl_strlen(char *store)
{
	size_t	i;

	i = 0;
	while (store[i] != '\0')
	{
		if (store[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

int	newl_check(char *store)
{
	size_t	i;

	i = 0;
	if (store == NULL)
		return (0);
	while (store[i] != '\0')
	{
		if (store[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*fetch_rest(char *store)
{
	char	*rest;
	size_t	i;
	size_t	len;

	i = 0;
	len = newl_strlen(store);
	while (store[len + i] != '\0')
		i++;
	rest = malloc(sizeof(char) * i + 1);
	if (rest == NULL)
		return (free(store), NULL);
	i = 0;
	while (store[len + i] != '\0')
	{
		rest[i] = store[len + i];
		i++;
	}
	rest[i] = '\0';
	free(store);
	return (rest);
}

char	*fetch_line(char *store)
{
	char	*full_line;
	size_t	i;
	size_t	len;

	i = 0;
	len = newl_strlen(store);
	full_line = malloc(sizeof(char) * len + 1);
	if (full_line == NULL)
		return (free(store), NULL);
	while (store[i] != '\0' && len > i)
	{
		full_line[i] = store[i];
		i++;
	}
	full_line[i] = '\0';
	return (full_line);
}
