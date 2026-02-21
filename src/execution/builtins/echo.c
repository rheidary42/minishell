/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:45:34 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/06 19:45:35 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (false);
	i++;
	if (str[i] == '\0')
		return (false);
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (false);
	return (true);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 1;
	while (cmd->argv[i] && is_flag(cmd->argv[i]) == 1)
	{
		new_line = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		write(STDOUT_FILENO, cmd->argv[i], ft_strlen(cmd->argv[i]));
		if (cmd->argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (new_line == 1)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
