/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <boenkhja@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 03:01:29 by boenkhja          #+#    #+#             */
/*   Updated: 2025/05/21 03:01:30 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 99
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	my_strlen(char *s);
size_t	newl_strlen(char *store);
int		newl_check(char *buffer);
char	*fetch_rest(char *store);
char	*fetch_line(char *store);

#endif
