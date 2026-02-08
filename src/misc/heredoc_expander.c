/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:38:54 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 03:38:55 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_len(char *s)
{
	char	*value;
	int		len;

	value = getenv(s);
	if (value == NULL)
		return (0);
	len = 0;
	while (value[len] != '\0')
		len++;
	return (len);
}

char	*var_name(t_shell *shell, char *s)
{
	char	*name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != '\0' && ft_isalnum(s[i]) == true)
		i++;
	name = arena_push(shell->arena, (sizeof(char) * i) + 1, 0, shell);
	while (i > j)
	{
		name[j] = s[j];
		j++;
	}
	return (name);
}

int	full_line_len(t_shell *shell, char *line)
{
	char	*name;
	int		exp_count;
	int		i;

	exp_count = 0;
	i = 0;
	while (line != NULL && line[i] != '\0')
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			exp_count = exp_count + 3 - 1;
			i++;
		}
		else if (line[i] == '$')
		{
			name = var_name(shell, &line[i + 1]);
			exp_count = exp_count + var_len(name) - 1;
		}
		i++;
	}
	return (i + exp_count);
}

void	copy_exit_code(t_shell *shell, char *exp_line, int *exp_i)
{
	char	*exit_code;
	int		i;

	exit_code = ft_itoa(shell->last_exit_status);
	i = 0;
	while (exit_code[i] != 0)
	{
		exp_line[i] = exit_code[i];
		i++;
	}
	*exp_i = *exp_i + i;
}

int	expand_var(t_shell *shell, char *exp_line, char *line, int *exp_i)
{
	char	*value;
	char	*name;
	int		i;

	name = var_name(shell, line);
	value = getenv(name);
	if (value == NULL)
		return (ft_strlen(name));
	i = 0;
	while (value[i] != '\0')
	{
		exp_line[i] = value[i];
		i++;
	}
	*exp_i = *exp_i + i;
	return (ft_strlen(name));
}
