#include "minishell.h"

// Minimal stub for builtins to allow linking during development.
// Replace with real builtin implementations later.
int	exec_builtin(t_cmd *cmd, char **envp, t_env *env, int builtin_id)
{
	if (builtin_id == EECHO)
		return (ft_echo(cmd));
	// if (builtin_id == CD)
	// 	return (ft_cd(cmd));
	if (builtin_id == PWD)
		return (ft_pwd());
	// if (builtin_id == EXPORT)
	// 	return (ft_export(cmd));
	if (builtin_id == UNSET)
		return (ft_unset(env, cmd));
	if (builtin_id == ENV)
		return (ft_env(envp));
	// if (builtin_id == EXIT)
	// 	return (ft_exit(cmd));
	// Return 0 to indicate success by default.
	return (0);
}
