/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 04:09:06 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 04:09:07 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	full_exit(t_shell *shell, int exit_code)
{
	rl_clear_history();
	if (shell->arena)
		free(shell->arena);
	if (shell->env)
		free_env(&shell->env);
	if (shell->line)
		free(shell->line);
	if (shell)
		free(shell);
	exit(exit_code);
}

void	close_fds(t_exec *exec)
{
	if (exec->pipe_fds[0] != -1)
	{
		close(exec->pipe_fds[0]);
		exec->pipe_fds[0] = -1;
	}
	if (exec->pipe_fds[1] != -1)
	{
		close(exec->pipe_fds[1]);
		exec->pipe_fds[1] = -1;
	}
	if (exec->file_fd != -1)
	{
		close(exec->file_fd);
		exec->file_fd = -1;
	}
}

void	free_and_close(t_shell *shell, t_cmd *cmd, t_exec *exec)
{
	int	ret;

	(void)cmd;
	ret = shell->last_exit_status;
	close_fds(exec);
	if (shell->arena)
	{
		free(shell->arena);
		shell->arena = NULL;
	}
	free_env(&shell->env);
	if (shell)
	{
		free(shell);
		shell = NULL;
	}
	exit(ret);
}

void	free_env(t_env **env)
{
	t_env	*curr;
	t_env	*tmp;

	if (!env)
		return ;
	curr = *env;
	while (curr != NULL)
	{
		tmp = curr->next;
		if (curr->name)
			free(curr->name);
		if (curr->value)
			free(curr->value);
		free(curr);
		curr = tmp;
	}
	*env = NULL;
	env = NULL;
}

void	clean_up(t_shell *shell)
{
	if (!shell)
		return ;
	full_exit(shell, 1);
}
