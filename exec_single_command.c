#include "minishell.h"

void	apply_redir(t_shell *shell, t_cmd *cmd, t_redir *redirection, t_exec *exec)
{
	t_redir	*r;

	r = redirection;
	while (r != NULL)
	{
		if (r->type == TOKEN_REDIR_OUT)
			exec->file_fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (r->type == TOKEN_APPEND)
			exec->file_fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (r->type == TOKEN_REDIR_IN)
			exec->file_fd = open(r->file, O_RDONLY);
		else if (r->type == TOKEN_HEREDOC)
			exec->file_fd = handle_heredoc(r->file);
		if (exec->file_fd == -1)
		{
			free_and_close(shell, cmd, exec);
			perror(r->file);
			exit(1);
		}
		if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_HEREDOC)
			dup2(exec->file_fd, STDIN_FILENO);
		if (r->type == TOKEN_REDIR_OUT || r->type == TOKEN_APPEND)
			dup2(exec->file_fd, STDOUT_FILENO);
		close(exec->file_fd);
		r = r->next;
	}
}

void	exec_in_child(t_shell *shell, t_cmd *cmd, t_exec *exec)
{
	char	**envp;

	apply_redir(shell, cmd, cmd->redir, exec);
	if (is_direct_path(cmd->argv[0]) == true)
		exec->final_path = cmd->argv[0];
	else
		path_lookup(cmd->argv[0], shell, exec);
	if (exec->final_path == NULL)
	{
		free_and_close(shell, cmd, exec);
		printf("%s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	envp = convert_envp(shell);
	execve(exec->final_path, cmd->argv, shell->env);
	perror(cmd->argv[0]);
	exit(127);
}

int	exec_ext_cmd(t_shell *shell, t_cmd *cmd, t_exec *exec)
{
	int	status;

	status = 0;
	exec->child = fork();
	if (exec->child == -1)
	{
		perror("fork failure");
		return (1);
	}
	if (exec->child == 0)
	{
		exec_in_child(shell, cmd, exec);
	}
	waitpid(exec->child, &status, 0);
	if (WIFEXITED(status) != 0)
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) != 0)
		shell->last_exit_status = 128 + WTERMSIG(status);
	return (shell->last_exit_status);
}

int	exec_single_cmd(t_shell *shell, t_exec *exec)
{
	t_cmd	*cmd;

	cmd = shell->cmds;
	if (cmd->argv == NULL || cmd->argv[0] == NULL)
	{
		//no command;
		return (0);
	}
	if (is_builtin(cmd) == true)
	{
		return (exec_builtin(cmd));
	}
	return (exec_ext_cmd(shell, cmd, exec));
}