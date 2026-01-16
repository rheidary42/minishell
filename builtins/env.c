#include "minishell.h"

int	ft_env(char **env)
{
	int	i;

	while (env && env[i])
	{
		write(STDOUT_FILENO, env[i], ft_strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}