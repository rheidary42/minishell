/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 01:55:38 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 01:55:39 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_failure(t_shell *shell, t_cmd *cmd, t_exec *exec)
{
	perror("fork failed\n");
	free_and_close(shell, cmd, exec);
}

void	redirection(t_exec *exec)
{
	close(exec->pipe_fds[1]);
	exec->prev_fd = exec->pipe_fds[0];
}

void	wait_for_children(t_shell *shell, t_exec *exec)
{
	pid_t	temp_pid;
	int		status;
	int		sig_num;

	sig_num = 0;
	while (1)
	{
		temp_pid = wait(&status);
		if (temp_pid == -1)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
		if (WIFSIGNALED(status) != 0)
		{
			sig_num = WTERMSIG(status);
			exec->sig_flag = 1;
		}
		if (temp_pid == exec->last_child && WIFEXITED(status) != 0)
			shell->last_exit_status = WEXITSTATUS(status);
	}
	if (exec->sig_flag == 1)
		sig_err_msg(shell, sig_num);
}

void	exec_cmd(t_shell *shell, t_cmd *cmd, t_exec *exec)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (exec->prev_fd != -1)
	{
		if (dup2(exec->prev_fd, STDIN_FILENO) == -1)
		{
			free_and_close(shell, cmd, exec);
			perror("dup2");
			exit(1);
		}
		close(exec->prev_fd);
	}
	if (cmd->next != NULL)
	{
		if (dup2(exec->pipe_fds[1], STDOUT_FILENO) == -1)
		{
			free_and_close(shell, cmd, exec);
			perror("dup2");
			exit(1);
		}
		close(exec->pipe_fds[0]);
		close(exec->pipe_fds[1]);
	}
	exec_in_child_helper(shell, cmd, exec);
}

int	build_pipeline(t_shell *shell, t_exec *exec)
{
	t_cmd	*cmd;

	cmd = shell->cmds;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (cmd != NULL)
	{
		if (cmd->next != NULL)
			if (pipe(exec->pipe_fds) == -1)
				perror("pipe failed\n");
		exec->child = fork();
		if (exec->child == -1)
			fork_failure(shell, cmd, exec);
		else if (exec->child == 0)
			exec_cmd(shell, cmd, exec);
		if (exec->prev_fd != -1)
			close(exec->prev_fd);
		if (cmd->next != NULL)
			redirection(exec);
		cmd = cmd->next;
		exec->last_child = exec->child;
	}
	wait_for_children(shell, exec);
	setup_signals(shell);
	return (shell->last_exit_status);
}
