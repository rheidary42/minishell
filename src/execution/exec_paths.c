/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:01:52 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 03:01:53 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_paths_from_env(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->name, "PATH", 4) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

int	count_path(char *paths_from_env)
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

char	*split_paths_helper(t_shell *shell, char *paths, int *e, int *s)
{
	char	*path;
	int		end;
	int		start;
	char	*paths_from_env;

	paths_from_env = paths;
	end = *e;
	start = *s;
	path = (char *)arena_push(shell->arena, end - start + 1, 0, shell);
	ft_strlcpy(path, paths_from_env + start, end - start + 1);
	*s = *e + 1;
	return (path);
}

char	**split_paths(char *paths_from_env, t_shell *shell)
{
	char	**all_paths;
	int		path_count;
	int		end;
	int		start;

	end = 0;
	start = 0;
	if (paths_from_env == NULL)
		return (NULL);
	path_count = count_path(paths_from_env);
	all_paths = (char **)arena_push(shell->arena, sizeof(char *)
			* (path_count + 1), 0, shell);
	path_count = 0;
	while (paths_from_env[end] != '\0')
	{
		if (paths_from_env[end] == ':')
			all_paths[path_count++] = split_paths_helper(shell,
					paths_from_env, &end, &start);
		end++;
	}
	if (end - start > 0)
		all_paths[path_count] = split_paths_helper(shell,
				paths_from_env, &end, &start);
	all_paths[path_count] = NULL;
	return (all_paths);
}

char	*check_executable(char **all_paths, char *cmd_name, t_shell *shell)
{
	char	*temp;
	int		i;

	i = 0;
	if (all_paths == NULL || cmd_name == NULL || cmd_name[0] == '\0')
		return (NULL);
	while (all_paths[i] != NULL)
	{
		temp = str_join3(all_paths[i], "/", cmd_name, shell);
		if (access(temp, X_OK) == 0)
			return (temp);
		i++;
	}
	return (NULL);
}
