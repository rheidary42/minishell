#include "minishell.h"

int	is_num(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_shell *shell, t_cmd *cmd, t_env *env)
{
	int	exit_argc;

	exit_argc = 0;
	while (cmd->argv[exit_argc + 1] != NULL)
		exit_argc++;
	if (exit_argc == 0)
	{
		free_env_list(env);
		exit(shell->last_exit_status);
	}
	if (is_num(cmd->argv[1]) == 0)
	{
		free_env_list(env);
		write(STDERR_FILENO, "exit: ", 7);
		write(STDERR_FILENO, cmd->argv[1], ft_strlen(cmd->argv[exit_argc]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		exit(2);
	}
	if (exit_argc == 1)
	{
		free_env_list(env);
		shell->last_exit_status = ft_atoi(cmd->argv[exit_argc]) % 256;
		exit(shell->last_exit_status);
	}
	if (exit_argc > 1)
	{
			write(STDERR_FILENO, "exit: ", 7);
			write(STDERR_FILENO, "too many arguments\n", 19);
			return (1);
	}
	return (0);
}
