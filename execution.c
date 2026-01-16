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

int	execution(t_shell *shell)
{
	t_exec	exec;

	if (shell->cmds == NULL)
	{
		// no commands;
		return (1);
	}
	initialise_exec(&exec);
	if (shell->cmds->next == NULL)
	{
		return (exec_single_cmd(shell, &exec));
	}
	return (build_pipeline(shell, &exec));
}