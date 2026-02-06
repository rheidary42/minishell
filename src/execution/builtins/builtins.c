/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:47:26 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/06 19:47:27 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_shell *shell, t_cmd *cmd, t_env *env, int builtin_id)
{
	setup_signals(shell);
	if (builtin_id == EECHO)
		return (ft_echo(cmd));
	if (builtin_id == CD)
		return (ft_cd(env, cmd));
	if (builtin_id == PWD)
		return (ft_pwd());
	if (builtin_id == EXPORT)
		return (ft_export(shell, env, cmd));
	if (builtin_id == UNSET)
		return (ft_unset(env, cmd));
	if (builtin_id == ENV)
		return (ft_env(env));
	if (builtin_id == EXIT)
		return (ft_exit(shell, cmd, env));
	return (0);
}
