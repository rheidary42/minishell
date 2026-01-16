#include "minishell.h"

void	wait_for_children(t_shell *shell, t_exec *exec)
{
	pid_t	temp_pid;
	int		status;

	temp_pid = 1;
	while (temp_pid > 0)
	{
		temp_pid = wait(&status);
		if (temp_pid == exec->last_child)
		{
			if (WIFEXITED(status) != 0)
				shell->last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status) != 0)
				shell->last_exit_status = 128 + WTERMSIG(status);
		}
	}
}

void	exec_cmd(t_shell *shell, t_cmd *cmd, t_exec *exec)
{
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
	while (cmd != NULL)
	{
		if (cmd->next != NULL)
			if (pipe(exec->pipe_fds) == -1)
				perror("pipe");
		exec->child = fork();
		if (exec->child == -1)
			return (perror("fork"), 1);
		else if (exec->child == 0)
			exec_cmd(shell, cmd, exec);
		if (exec->prev_fd != -1)
			close(exec->prev_fd);
		if (cmd->next != NULL)
		{
			close(exec->pipe_fds[1]);
			exec->prev_fd = exec->pipe_fds[0];
		}
		cmd = cmd->next;
		exec->last_child = exec->child;
	}
	wait_for_children(shell, exec);
	return (shell->last_exit_status);
}
