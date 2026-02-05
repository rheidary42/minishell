#include "minishell.h"

int	is_num(char *s)
{
	int	i;

	i = 0;
	if (s != NULL && (s[0] == '+' || s[0] == '-'))
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(char *s)
{
	long	result;
	long	prev;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] != '\0')
	{
		prev = result;
		result = result * 10 + (s[i] - '0');
		if (result / 10 != prev)
		{
			return (-1);
		}
		i++;
	}
	return (result * sign);
}

void	cleanup_and_exit(t_shell *shell, int exit_code)
{
	write(STDERR_FILENO, "exit\n", 5);
	free_env(&shell->env);
	free(shell->arena);
	free(shell);
	exit(exit_code);
}

void	handle_exit_error(t_shell *shell, char *arg, char *s)
{
	write(STDERR_FILENO, "exit\n", 5);
	write(STDERR_FILENO, "exit: ", 6);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
	free_env(&shell->env);
	free(shell->arena);
	free(shell);
	free(s);
	exit(2);
}

void	handle_single_arg(t_shell *shell, t_cmd* cmd, char *s)
{
	long	exit_code;
	int		flag;

	flag = 0;
	if (ft_strcmp(cmd->argv[1], "-1") == 0)
	{
		exit_code = -1;
		flag = 1;
	}
	exit_code = ft_atol(cmd->argv[1]);
	if (exit_code == -1 && flag == 0)
		handle_exit_error(shell, cmd->argv[1], s);
	else
	{
		free(s);
		cleanup_and_exit(shell, exit_code % 256);
	}
}

int	ft_exit(t_shell *shell, t_cmd *cmd, t_env *env)
{
	char	*tmp;
	int		exit_argc;
	int		exit_code;

	exit_code = 0;
	exit_argc = 0;
	while (cmd->argv[exit_argc + 1] != NULL)
		exit_argc++;
	if (exit_argc == 0)
		cleanup_and_exit(shell, shell->last_exit_status);
	tmp = ft_strtrim(cmd->argv[1], " \t\n\v\f\r");
	cmd->argv[1] = tmp;
	if (is_num(cmd->argv[1]) == 0)
		handle_exit_error(shell, cmd->argv[1], tmp);
	if (exit_argc == 1)
		handle_single_arg(shell, cmd, tmp);
	if (exit_argc > 1)
	{
		free(tmp);
		write(STDERR_FILENO, "exit\nexit: too many arguments\n", 31);
		return (1);
	}
	return (0);
}
