#include "minishell.h"

int	ft_env(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr != NULL)
	{
		if (curr->exported == true)
		{
			write(STDOUT_FILENO, curr->name, ft_strlen(curr->name));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, curr->value, ft_strlen(curr->value));
			write(STDOUT_FILENO, "\n", 1);
		}
		curr = curr->next;
	}
	return (0);
}