#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (EECHO);
	if (ft_strcmp(cmd, "cd") == 0)
		return (CD);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(cmd, "export") == 0)
		return (EXPORT);
	if (ft_strcmp(cmd, "unset") == 0)
		return (UNSET);
	if (ft_strcmp(cmd, "env") == 0)
		return (ENV);
	if (ft_strcmp(cmd, "exit") == 0)
		return (EXIT);
	return (-1);
}

void	free_heredocs(t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*r;

	cmd = shell->cmds;
	while (cmd != NULL)
	{
		r = cmd->redir;
		while (r != NULL)
		{
			if (r->type == TOKEN_HEREDOC && r->file != NULL)
			{
				unlink(r->file);
				free(r->file);
				r->file = NULL;
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
}

int	execution(t_shell *shell)
{
	t_exec	exec;

	if (shell->cmds == NULL)
	{
		// no commands;
		return (1);
	}
	setup_prompt_signals();
	initialise_exec(&exec);
	if (heredoc_collector(shell) == 1)
	{
		shell->last_exit_status = 130;
	//	free_heredocs(shell);
		return (1);
	}
	if (shell->cmds->next == NULL)
	{
		return (exec_single_cmd(shell, &exec));
	}
	return (build_pipeline(shell, &exec));
}