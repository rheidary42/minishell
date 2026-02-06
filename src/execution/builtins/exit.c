/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:44:38 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/06 19:44:39 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_arg(t_shell *shell, t_cmd *cmd, char *s)
{
	long	exit_code;
	int		flag;

	flag = 0;
	if (ft_strcmp(cmd->argv[1], "-1") == 0)
	{
		exit_code = -1;
		flag = 1;
	}
	exit_code = ft_atol(cmd->argv[1]);
	if (exit_code == -1 && flag == 0)
		handle_exit_error(shell, cmd->argv[1], s);
	else
	{
		free(s);
		cleanup_and_exit(shell, exit_code % 256);
	}
}

int	ft_exit(t_shell *shell, t_cmd *cmd, t_env *env)
{
	char	*tmp;
	int		exit_argc;
	int		exit_code;

	exit_code = 0;
	exit_argc = 0;
	while (cmd->argv[exit_argc + 1] != NULL)
		exit_argc++;
	if (exit_argc == 0)
		cleanup_and_exit(shell, shell->last_exit_status);
	tmp = ft_strtrim(cmd->argv[1], " \t\n\v\f\r");
	cmd->argv[1] = tmp;
	if (is_num(cmd->argv[1]) == 0)
		handle_exit_error(shell, cmd->argv[1], tmp);
	if (exit_argc == 1)
		handle_single_arg(shell, cmd, tmp);
	if (exit_argc > 1)
	{
		free(tmp);
		write(STDERR_FILENO, "exit\nexit: too many arguments\n", 31);
		return (1);
	}
	return (0);
}
