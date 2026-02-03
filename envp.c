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

// On return 0 cleanup, maybe not cleanup function but only going through array
int	copy_var(t_env *env, char *str)
{
	size_t	name_len;
	size_t	value_len;

	name_len = strlen_delim(str, '=');
	if (str[name_len] == '\0')		//no "=" found
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
		return (free(env->name), 0);
	ft_strlcpy(env->name, str, name_len + 1);
	ft_strlcpy(env->value, str + name_len + 1, value_len + 1);
	env->exported = true;
	return (1);
}

int	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = tmp;
	}
	return (0);
}

// ! TODO: MAKE ENV (3 THINGS IDK) 
// ! IN CASE OF ENV -I ./MINISHELL START UP LEADING TO NO ENV
// int	make_envp(t_env *copy_env)
// {
	
// 	return (0);
// }

int	copy_envp(t_env *copy_env, char **curr_env)
{
	t_env	*curr_node;
	t_env	*new_node;
	int		i;

	i = 0;
	if (!copy_env)
		return (EXIT_FAILURE);
	// if (!curr_env)
	// 	return (make_envp(copy_env));
	curr_node = copy_env;
	while (curr_env[i] != NULL)
	{
		if (copy_var(curr_node, curr_env[i++]) == 0)
			return (free_env_list(copy_env));
		if (curr_env[i] == NULL)
			break ;
		new_node = ft_calloc(1, sizeof(t_env));
		if (new_node == NULL)
			return (free_env_list(copy_env));
		curr_node->next = new_node;
		curr_node = new_node;
	}
	if (curr_node != NULL)
		curr_node->next = NULL;
	return (0);
}
