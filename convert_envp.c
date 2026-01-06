#include "minishell.h"

int	env_list_size(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**convert_envp(t_shell *shell)
{
	t_env	*curr_env;
	char	**env;
	int		list_size;
	int		i;

	curr_env = shell->env;
	list_size = env_list_size(curr_env);
	env = (char **)arena_push(shell->arena, sizeof(char *) * (list_size + 1), 0);
	i = 0;
	while (curr_env != NULL)
	{
		env[i] = str_join3(curr_env->name, "=", curr_env->value, shell);
		i++;
		curr_env = curr_env->next;
	}
	env[i] = NULL;
	return (env);
}
