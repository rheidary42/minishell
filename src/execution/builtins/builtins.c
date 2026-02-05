#include "minishell.h"

// Minimal stub for builtins to allow linking during development.
// Replace with real builtin implementations later.
int	exec_builtin(t_shell *shell, t_cmd *cmd, char **envp, t_env *env, int builtin_id)
{
	setup_signals(shell);
	if (builtin_id == EECHO)
		return (ft_echo(cmd));
	if (builtin_id == CD)
		return (ft_cd(env, cmd));
	if (builtin_id == PWD)
		return (ft_pwd());
	if (builtin_id == EXPORT)
		return (ft_export(shell, env, cmd));
	if (builtin_id == UNSET)
		return (ft_unset(env, cmd));
	if (builtin_id == ENV)
		return (ft_env(env));
	if (builtin_id == EXIT)
		return (ft_exit(shell, cmd, env));
	return (0);
}
