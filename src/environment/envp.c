/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:03:06 by rheidary          #+#    #+#             */
/*   Updated: 2026/02/03 12:09:11 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	strlen_delim(char *str, char delim)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != delim)
		i++;
	return (i);
}

int	copy_var(t_env *env, char *str)
{
	size_t	name_len;
	size_t	value_len;

	name_len = strlen_delim(str, '=');
	if (str[name_len] == '\0')
	{
		env->name = ft_strdup(str);
		env->value = ft_strdup("");
		env->exported = true;
		if (!env->name || !env->value)
			return (0);
		return (1);
	}
	value_len = strlen_delim(str + name_len + 1, '\0');
	env->name = ft_calloc(1, name_len + 1);
	if (env->name == NULL)
		return (0);
	env->value = ft_calloc(1, value_len + 1);
	if (env->value == NULL)
		return (free(env->name), env->name = NULL, 0);
	ft_strlcpy(env->name, str, name_len + 1);
	ft_strlcpy(env->value, str + name_len + 1, value_len + 1);
	env->exported = true;
	return (1);
}

int	add_env_var(t_shell *shell, t_env *node, char *name, char *value)
{
	(void)shell;
	if (node->name != NULL)
		free(node->name);
	node->name = ft_strdup(name);
	if (node->name == NULL)
		return (1);
	if (node->value != NULL)
		free(node->value);
	node->value = ft_strdup(value);
	if (node->value == NULL)
		return (1);
	node->exported = true;
	return (0);
}

int	make_envp(t_shell *shell, t_env *copy_env)
{
	t_env	*new_node;
	char	*pwd;
	char	*shlvl;

	pwd = getcwd(NULL, 0);
	if (add_env_var(shell, copy_env, "PWD", pwd) == 1)
		return (free_env(&copy_env), 1);
	free(pwd);
	new_node = ft_calloc(1, sizeof(t_env));
	if (new_node == NULL)
		return (free_env(&copy_env), 1);
	copy_env->next = new_node;
	shlvl = ft_itoa(shell->shlvl);
	if (add_env_var(shell, copy_env->next, "SHLVL", shlvl) == 1)
		return (free(shlvl), free_env(&copy_env), 1);
	free(shlvl);
	new_node = ft_calloc(1, sizeof(t_env));
	if (new_node == NULL)
		return (free_env(&copy_env), 1);
	copy_env->next->next = new_node;
	if (add_env_var(shell, copy_env->next->next, "_", "/usr/bin/env") == 1)
		return (free_env(&copy_env), 1);
	copy_env->next->next->next = NULL;
	return (0);
}

int	copy_envp(t_shell *shell, t_env *copy_env, char **curr_env)
{
	t_env	*curr_node;
	t_env	*new_node;
	int		i;

	i = 0;
	if (!copy_env)
		return (EXIT_FAILURE);
	if (!curr_env || !curr_env[0])
		return (make_envp(shell, copy_env));
	curr_node = copy_env;
	while (curr_env[i] != NULL)
	{
		if (copy_var(curr_node, curr_env[i++]) == 0)
			return (free_env(&copy_env), 1);
		if (curr_env[i] == NULL)
			break ;
		new_node = ft_calloc(1, sizeof(t_env));
		if (new_node == NULL)
			return (free_env(&copy_env), 1);
		curr_node->next = new_node;
		curr_node = new_node;
	}
	if (curr_node != NULL)
		curr_node->next = NULL;
	return (0);
}
