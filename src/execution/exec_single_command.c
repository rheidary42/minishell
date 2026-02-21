/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:02:01 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 03:02:02 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	consume_redirs_only(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type == TOKEN_REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == TOKEN_APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(redir->file);
			return (-1);
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
}

int	apply_redir(t_shell *shell, t_redir *redirection, t_exec *exec)
{
	t_redir	*r;

	r = redirection;
	while (r != NULL && r->file != NULL)
	{
		if (r->type == TOKEN_REDIR_OUT)
			exec->file_fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (r->type == TOKEN_APPEND)
			exec->file_fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_HEREDOC)
			exec->file_fd = open(r->file, O_RDONLY);
		if (exec->file_fd == -1)
		{
			if (r && r->file)
				perror(r->file);
			return (set_exit_status(shell));
		}
		if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_HEREDOC)
			dup2(exec->file_fd, STDIN_FILENO);
		else if (r->type == TOKEN_REDIR_OUT || r->type == TOKEN_APPEND)
			dup2(exec->file_fd, STDOUT_FILENO);
		close(exec->file_fd);
		r = r->next;
	}
	return (0);
}

void	exec_in_child_helper(t_shell *shell, t_cmd *cmd, t_exec *exec)
{
	char	**envp;

	if (apply_redir(shell, cmd->redir, exec) == 1)
		free_and_close(shell, cmd, exec);
	envp = set_envp(shell, cmd, exec, &exec->builtin_id);
	if (exec->builtin_id >= 0)
	{
		exec_builtin(shell, cmd, shell->env, exec->builtin_id);
		free_and_close(shell, cmd, exec);
	}
	if (is_direct_path(cmd->argv[0]) == true)
	{
		exec->final_path = (char *)arena_push(shell->arena,
				ft_strlen(cmd->argv[0]) + 1, 0, shell);
		ft_strlcpy(exec->final_path, cmd->argv[0], ft_strlen(cmd->argv[0]) + 1);
		free_env(&shell->env);
	}
	else
		path_lookup(cmd->argv[0], shell, exec);
	if (exec->final_path == NULL)
		no_final_path(shell, cmd, exec, envp);
	close_shell_fds(shell);
	execve(exec->final_path, cmd->argv, envp);
	exec->errno_save = errno;
	read_errno(shell, cmd, exec);
}

int	exec_in_child(t_shell *shell, t_cmd *cmd, t_exec *exec)
{
	int	status;

	status = 0;
	exec->child = fork();
	if (exec->child == -1)
		fork_failure(shell, cmd, exec);
	if (exec->child == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_in_child_helper(shell, cmd, exec);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(exec->child, &status, 0);
	setup_signals(shell);
	if (WIFEXITED(status) != 0)
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) != 0)
		detect_signals(shell, status);
	return (shell->last_exit_status);
}

int	exec_single_cmd(t_shell *shell, t_exec *exec)
{
	t_cmd	*cmd;
	int		builtin_id;

	cmd = shell->cmds;
	if (cmd->argv == NULL || cmd->argv[0] == NULL)
	{
		if (cmd->redir != NULL)
		{
			if (consume_redirs_only(cmd->redir) == -1)
				shell->last_exit_status = 1;
			else
				shell->last_exit_status = 0;
		}
		return (shell->last_exit_status);
	}
	builtin_id = is_builtin(cmd->argv[0]);
	if (builtin_id >= 0)
	{
		if (apply_redir(shell, cmd->redir, exec) == 1)
			free_and_close(shell, shell->cmds, exec);
		shell->last_exit_status = exec_builtin(shell, cmd,
				shell->env, builtin_id);
		return (shell->last_exit_status);
	}
	return (exec_in_child(shell, cmd, exec));
}
