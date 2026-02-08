/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:19:42 by rheidary          #+#    #+#             */
/*   Updated: 2026/02/02 20:07:13 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_var_len(char *value, int *var_start, t_shell *shell)
{
	char	*var_name;
	int		var_end;
	t_env	*head;
	size_t	len;

	len = 0;
	if (value[*var_start] == '?')
		return (*var_start += 1, exit_status_len(shell->last_exit_status));
	var_end = *var_start;
	while (value[var_end] && (ft_isalnum(value[var_end])) != 0)
		var_end++;
	var_name = arena_push(shell->arena, var_end - *var_start + 1, 0, shell);
	ft_strlcpy(var_name, &value[*var_start], var_end - *var_start + 1);
	head = shell->env;
	while (head != NULL)
	{
		if (ft_strcmp(head->name, var_name) == 0)
		{
			len = ft_strlen(head->value);
			break ;
		}
		head = head->next;
	}
	*var_start = var_end;
	return (len);
}

char	*get_var_name(t_shell *shell, char *value, size_t *var_start)
{
	size_t	var_end;
	char	*var_name;

	var_end = *var_start;
	while (value[var_end] && (ft_isalnum(value[var_end])) != 0)
		var_end++;
	var_name = (char *)arena_push(shell->arena,
			var_end - *var_start + 1, 0, shell);
	ft_strlcpy(var_name, value + *var_start, var_end - *var_start + 1);
	*var_start = var_end;
	return (var_name);
}

char	*get_var_value(char *var_name, t_shell *shell)
{
	t_env	*head;
	char	*result;

	head = shell->env;
	while (head != NULL)
	{
		if (ft_strcmp(head->name, var_name) == 0)
		{
			{
				result = (char *)arena_push(shell->arena,
						ft_strlen(head->value) + 1, 0, shell);
				ft_strlcpy(result, head->value, ft_strlen(head->value) + 1);
				return (result);
			}
		}
		head = head->next;
	}
	return (NULL);
}
