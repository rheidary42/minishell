/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:44:57 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/06 19:45:01 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_num(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	if (s != NULL && (s[0] == '+' || s[0] == '-'))
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(char *s)
{
	long	result;
	long	prev;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] != '\0')
	{
		prev = result;
		result = result * 10 + (s[i] - '0');
		if (result / 10 != prev)
		{
			return (-1);
		}
		i++;
	}
	return (result * sign);
}

void	cleanup_and_exit(t_shell *shell, int exit_code)
{
	write(STDERR_FILENO, "exit\n", 5);
	free_env(&shell->env);
	free(shell->arena);
	free(shell);
	exit(exit_code);
}

void	handle_exit_error(t_shell *shell, char *arg, char *s)
{
	write(STDERR_FILENO, "exit\n", 5);
	write(STDERR_FILENO, "exit: ", 6);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
	free_env(&shell->env);
	free(shell->arena);
	free(shell);
	free(s);
	exit(2);
}
