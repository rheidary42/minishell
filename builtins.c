#include "minishell.h"

// Minimal stub for builtins to allow linking during development.
// Replace with real builtin implementations later.
int	exec_builtin(t_cmd *cmd, char **envp)
{
	(void)cmd;
	(void)envp;
	ft_echo(cmd);
	// Return 0 to indicate success by default.
	return (0);
}
