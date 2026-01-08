/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <boenkhja@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:59:33 by boenkhja          #+#    #+#             */
/*   Updated: 2025/05/28 12:32:02 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	i;

	i = 0;
	res = NULL;
	if (nmemb == 0 || size == 0)
	{
		res = (void *)malloc(0);
		if (res == NULL)
			return (NULL);
		return (res);
	}
	if (nmemb > (i - 1) / size)
		return (NULL);
	res = (void *)malloc(nmemb * size);
	if (res == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		((char *)res)[i] = 0;
		i++;
	}
	return (res);
}

static char	*ft_strdup(char *buffer)
{
	char	*new;
	size_t	i;

	i = 0;
	new = ft_calloc(sizeof(char), my_strlen(buffer) + 1);
	if (new == NULL)
		return (NULL);
	while (buffer[i] != '\0')
	{
		new[i] = buffer[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char	*store_buffer(char *store, char *buffer, int bytes_read)
{
	char	*new_store;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (store == NULL)
		return (ft_strdup(buffer));
	new_store = ft_calloc(sizeof(char), (my_strlen(store) + bytes_read + 1));
	if (new_store == NULL)
		return (free(store), NULL);
	while (store[i] != '\0')
	{
		new_store[i] = store[i];
		i++;
	}
	while (buffer[j] != '\0')
	{
		new_store[i + j] = buffer[j];
		j++;
	}
	new_store[i + j] = '\0';
	if (store[my_strlen(store)] != '\n')
		free(store);
	return (new_store);
}

static int	read_line(char **store, char *buffer, int fd)
{
	int	bytes_read;

	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (free(buffer), -1);
	*store = store_buffer(*store, buffer, bytes_read);
	free(buffer);
	while (newl_check(*store) == 0 && bytes_read != 0)
	{
		buffer = ft_calloc(sizeof(char), bytes_read + 1);
		if (buffer == NULL)
			return (-1);
		bytes_read = read(fd, buffer, bytes_read);
		if (bytes_read < 0)
			return (free(buffer), -1);
		if (bytes_read == 0)
			return (free(buffer), 2);
		buffer[bytes_read] = '\0';
		*store = store_buffer(*store, buffer, bytes_read);
		free(buffer);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*new_line;
	char		*buffer;
	int			ret;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(store), NULL);
	ret = read_line(&store, buffer, fd);
	if (store == NULL || ret == -1)
		return (free(store), store = NULL, NULL);
	new_line = fetch_line(store);
	if (new_line == NULL)
		return (NULL);
	else if (store[0] == '\0' && new_line[0] == '\0')
		return (free(store), free(new_line), store = NULL, NULL);
	else
		store = fetch_rest(store);
	if (ret == 2)
	{
		free(store);
		store = NULL;
	}
	return (new_line);
}

// #include <fcntl.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
//     int fd = open("get_next_line.h", O_RDONLY);
//     char    *newl = "";
//     int i = 0;
//     // newl = get_next_line(fd);
//     // printf("line is: %s\n", newl);
//     // free(newl);
//     // newl = get_next_line(fd);
//     // printf("%s\n", newl);
//   //  free(newl);
//     while (newl != NULL)
//     {
//         newl = get_next_line(fd);
//         printf("line is: %s\n", newl);
//         free(newl);
//         if (i == 4)
//             fd = 42;
//         i++;
//     }
//     close(fd);
//     return 0;
// }
