#include "minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	while (cmd->argv[i] && ft_strncmp(cmd->argv[i], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		write(STDOUT_FILENO, cmd->argv[i], ft_strlen(cmd->argv[i]));
		if (cmd->argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline == 1)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
