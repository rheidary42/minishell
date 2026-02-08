/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:02:11 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 03:02:12 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_lookup(char *cmd_name, t_shell *shell, t_exec *exec)
{
	exec->paths_from_env = get_paths_from_env(shell->env);
	exec->all_paths = split_paths(exec->paths_from_env, shell);
	exec->final_path = check_executable(exec->all_paths, cmd_name, shell);
}

int	execution(t_shell *shell)
{
	t_exec	exec;

	if (shell->cmds == NULL)
		return (1);
	setup_signals(shell);
	initialise_exec(&exec);
	if (heredoc_collector(shell) == 1)
	{
		shell->last_exit_status = 130;
		return (1);
	}
	if (shell->cmds->next == NULL)
		return (exec_single_cmd(shell, &exec));
	return (build_pipeline(shell, &exec));
}
