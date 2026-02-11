/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:16:28 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/06 19:16:30 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_var(t_env *curr, char *var, int id_len)
{
	free(curr->value);
	curr->value = ft_calloc(ft_strlen(var) - id_len + 1, sizeof(char));
	if (curr->value == NULL)
		return (1);
	curr->has_equal_sign = 0;
	ft_strlcpy(curr->value, var + id_len + 1, ft_strlen(var) - id_len + 1);
	return (0);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cwd);
	return (0);
}
