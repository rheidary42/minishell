/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:42:40 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/06 19:44:32 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_id(char *s)
{
	int	i;

	if (!s || s[0] == '=')
		return (0);
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	just_export(t_env *env)
{
	while (env != NULL)
	{
		if (env->exported == true)
		{
			write(STDOUT_FILENO, "declare -x ", 12);
			write(STDOUT_FILENO, env->name, ft_strlen(env->name));
			if (env->value != NULL && env->has_equal_sign != 1)
			{
				write(STDOUT_FILENO, "=\"", 2);
				write(STDOUT_FILENO, env->value, ft_strlen(env->value));
				write(STDOUT_FILENO, "\"", 1);
			}
			write(STDOUT_FILENO, "\n", 1);
		}
		env = env->next;
	}
}

int	new_var(t_env *env, char *var)
{
	t_env	*new_node;
	t_env	*tmp;

	tmp = env;
	new_node = ft_calloc(1, sizeof(t_env));
	if (new_node == NULL)
		return (1);
	if (copy_var(new_node, var) == 0)
		return (1);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	return (0);
}

int	process_var(t_env *env, char *var)
{
	int		id_len;
	t_env	*curr;

	id_len = 0;
	curr = env;
	while (var[id_len] != '\0' && var[id_len] != '=')
		id_len++;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->name, var, id_len) == 0)
			break ;
		curr = curr->next;
	}
	if (curr == NULL)
		return (new_var(env, var));
	curr->exported = true;
	if (var[id_len] != '\0')
		return (change_var(curr, var, id_len));
	return (0);
}

int	ft_export(t_shell *shell, t_env *env, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->argv[1] == NULL)
		return (just_export(env), 0);
	while (cmd->argv[i] != NULL)
	{
		if (validate_id(cmd->argv[i]) == 0)
		{
			write(STDERR_FILENO, "export: `", 9);
			write(STDERR_FILENO, cmd->argv[i], ft_strlen(cmd->argv[i]));
			write(STDERR_FILENO, "': not a valid identifier\n", 26);
			shell->last_exit_status = 1;
			i++;
			continue ;
		}
		if (process_var(env, cmd->argv[i]) == 1)
		{
			return (free_env(&shell->env), 2);
		}
		i++;
	}
	return (shell->last_exit_status);
}
