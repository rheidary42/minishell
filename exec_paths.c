#include "minishell.h"

char	*get_paths_from_env(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->name, "PATH=", 5) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

int		count_path(char *paths_from_env)
{
	int	path_count;
	int	i;

	path_count = 1;
	i = 0;
	while (paths_from_env[i] != '\0')
	{
		if (paths_from_env[i] == ':')
			path_count++;
		i++;
	}
	return (path_count);
}

char	**split_paths(char *paths_from_env, t_shell *shell)
{
	char	**all_paths;
	int		path_count;
	int		end;
	int		start;

	end = 0;
	start = 0;
	path_count = count_path(paths_from_env);
	all_paths = safe_calloc(sizeof(char *) * (path_count + 1), shell);
	path_count = 0;
	while (paths_from_env[end] != '\0')
	{
		if (paths_from_env[end] == ':')
		{
			all_paths[path_count] = ft_substr(paths_from_env, start, end - start);
			if (all_paths[path_count] == NULL)
				return (free_func(all_paths, shell), NULL);
			path_count++;
			start = end + 1;
		}
		end++;
	}
	all_paths[path_count] = NULL;
	return (all_paths);
}

char	*check_executable(char **all_paths, char *cmd_name, t_shell *shell)
{
	char	*temp;
	int		i;

	i = 0;
	if (all_paths == NULL)
		return (NULL);
	while (all_paths[i] != NULL)
	{
		temp = custom_strjoin(all_paths[i], cmd_name, shell);
		if (temp == NULL)
			return (NULL);
		if (access(temp, X_OK) == 0)
			return (temp);
		i++;
		free(temp);
	}
	return (NULL);
}

void	path_lookup(char *cmd_name, t_shell *shell, t_exec *exec)
{
	exec->paths_from_env = get_paths_from_env(shell->env);
	exec->all_paths = split_paths(exec->paths_from_env, shell);
	exec->final_path = check_executable(exec->all_paths, cmd_name, shell);
}