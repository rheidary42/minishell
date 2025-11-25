/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:03:25 by rheidary          #+#    #+#             */
/*   Updated: 2025/11/25 05:21:52 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	exit_status_len(int i)
{
	if (i < 10)
		return (1);
	if (i < 100)
		return (2);
	return (3);
}

int	ifs(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}