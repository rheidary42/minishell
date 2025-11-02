#include "minishell.h"

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