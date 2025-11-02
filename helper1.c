/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:30:43 by rheidary          #+#    #+#             */
/*   Updated: 2025/11/02 20:04:58 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_safe_strdup(const char *s, t_shell *shell)
{
	char	*dup_str;
	char	*s_cast;

	dup_str = safe_calloc((ft_strlen(s) + 1), shell);
	s_cast = (char *)s;
	dup_str = ft_strcpy(dup_str, s_cast);
	return (dup_str);
}

char	*ft_strcpy(char *dest, char *src)
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
