/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 01:06:23 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 01:06:25 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialise_exec(t_exec *exec)
{
	ft_memset(exec, 0, sizeof(t_exec));
	exec->prev_fd = -1;
	exec->pipe_fds[0] = -1;
	exec->pipe_fds[1] = -1;
	exec->file_fd = -1;
}

bool	is_direct_path(char *executable)
{
	int	i;

	i = 0;
	while (executable[i] != '\0')
	{
		if (executable[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

void	str_join3_helper(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

char	*str_join3(char *s1, char *s2, char *s3, t_shell *shell)
{
	char	*str_comb;
	int		a;
	int		b;
	int		c;

	str_comb = (char *)arena_push(shell->arena, ft_strlen(s1) + ft_strlen(s2)
			+ ft_strlen(s3) + 1, 0, shell);
	a = 0;
	b = 0;
	c = 0;
	while (s1[a] != '\0')
	{
		str_comb[a] = s1[a];
		a++;
	}
	while (s2[b] != '\0')
	{
		str_comb[a + b] = s2[b];
		b++;
	}
	str_join3_helper(&str_comb[a + b], s3);
	return (str_comb);
}
