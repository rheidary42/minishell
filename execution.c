#include "minishell.h"

int	execution(t_shell *shell)
{
	if (shell->cmds == NULL)
	{
		// no commands;
		return (1);
	}
	if (shell->cmds->next == NULL)
	{
		exec_single_cmd(shell);
	}
}