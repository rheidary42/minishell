/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:45:25 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/06 19:45:27 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr != NULL)
	{
		if (curr->exported == true)
		{
			write(STDOUT_FILENO, curr->name, ft_strlen(curr->name));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, curr->value, ft_strlen(curr->value));
			write(STDOUT_FILENO, "\n", 1);
		}
		curr = curr->next;
	}
	return (0);
}
