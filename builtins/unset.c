#include "minishell.h"

int	is_valid_id(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	del_node(t_env *env, char *str)
{
	t_env	*curr;
	t_env	*prev;

	curr = env->next;
	prev = env;
	while (curr)
	{
		if (!ft_strcmp(curr->name, str))
		{
			prev->next = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(t_env *env, t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->argv[i])
	{
		if (is_valid_id(cmd->argv[i]))
			del_node(env, cmd->argv[i]);
		i++;
	}
	return (0);
}