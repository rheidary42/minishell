#include "minishell.h"

int	consume_redirs_only(t_shell *shell, t_redir *redir)
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
		redir = redir->next;
	}
	return (0);
}

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
		else if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_HEREDOC)
			exec->file_fd = open(r->file, O_RDONLY);
		if (exec->file_fd == -1)
		{
			free_and_close(shell, cmd, exec);
			perror(r->file);
			exit(1);
		}
		if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_HEREDOC)
			dup2(exec->file_fd, STDIN_FILENO);
		else if (r->type == TOKEN_REDIR_OUT || r->type == TOKEN_APPEND)
			dup2(exec->file_fd, STDOUT_FILENO);
		close(exec->file_fd);
		r = r->next;
	}
}

void	exec_in_child_helper(t_shell *shell, t_cmd *cmd, t_exec *exec)
{
	char	**envp;
	int		builtin_id;

	apply_redir(shell, cmd, cmd->redir, exec);
	if ((envp = convert_envp(shell)) == NULL)
	{
		printf("%s: 1heeeeeeeeeeeeere command not found\n", cmd->argv[0]);
		free_and_close(shell, cmd, exec);
		exit(1);
	}
	if ((builtin_id = is_builtin(cmd->argv[0])) >= 0)
	{
		shell->last_exit_status = exec_builtin(shell, cmd, envp, shell->env, builtin_id);
		int ret = shell->last_exit_status;
		free_and_close(shell, cmd, exec);
		exit(ret);
	}
	if (is_direct_path(cmd->argv[0]) == true)
	{
		exec->final_path = (char *)arena_push(shell->arena, ft_strlen(cmd->argv[0]) + 1, 0, shell);
		ft_strlcpy(exec->final_path, cmd->argv[0], ft_strlen(cmd->argv[0]) + 1);
		free_env_list(shell->env);
	}
	else
		path_lookup(cmd->argv[0], shell, exec);
	if (exec->final_path == NULL)
	{
		write(STDERR_FILENO, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(STDERR_FILENO, ": command not found\n", 21);
		free_and_close(shell, cmd, exec);
		exit(127);
	}
	execve(exec->final_path, cmd->argv, envp);
	exec->errno_save = errno;
	perror(cmd->argv[0]);
	free(shell->arena);
	free_and_close(shell, cmd, exec);
	if (exec->errno_save == EACCES)
		exit(126);
	else
		exit(127);
}

int	exec_in_child(t_shell *shell, t_cmd *cmd, t_exec *exec)
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
	{
		int gl_sig = WTERMSIG(status);
		if (gl_sig == SIGINT)
		{
			write(1, "\n", 1);
		}
		if (gl_sig == SIGQUIT)
		{
			write(1, "Quit (core dumped)\n", 20);
		}
		shell->last_exit_status = 128 + gl_sig;
	}
	return (shell->last_exit_status);
}

void	restore_std(int sin, int sout)
{
	dup2(sin, STDIN_FILENO);
	dup2(sout, STDOUT_FILENO);
	close(sin);
	close(sout);
}

int	exec_single_cmd(t_shell *shell, t_exec *exec)
{
	t_cmd	*cmd;
	int		builtin_id;
	int		save_stdin;
	int		save_stdout;

	cmd = shell->cmds;
	if (cmd->argv == NULL || cmd->argv[0] == NULL)
	{
		if (cmd->redir != NULL)
		{
			if (consume_redirs_only(shell, cmd->redir) == -1)
				shell->last_exit_status = 1;
			else
				shell->last_exit_status = 0;
		}
		return (shell->last_exit_status);
	}
	builtin_id = is_builtin(cmd->argv[0]);
	if (builtin_id >= 0)
	{
		save_stdin = dup(STDIN_FILENO);
		save_stdout = dup(STDOUT_FILENO);
		apply_redir(shell, cmd, cmd->redir, exec);
		shell->last_exit_status = exec_builtin(shell, cmd, convert_envp(shell),
							shell->env, builtin_id);
		restore_std(save_stdin, save_stdout);
		return (shell->last_exit_status);
	}
	return (exec_in_child(shell, cmd, exec));
}
