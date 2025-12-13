/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:03:25 by rheidary          #+#    #+#             */
/*   Updated: 2025/12/13 17:53:43 by rheidary         ###   ########.fr       */
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

int	is_expandable_var(char *value, size_t index, t_quote in_quote)
{
	char	c;
	char	next;

	if (in_quote == SINGLE_QUOTE)
		return (0);
	c = value[index];
	next = value[index + 1];
	return ((c == '$') && (ft_isalpha(next) || next == '?'));
}

//	NO_QUOTE -> not in quotes
//	SINGLE_QUOTE -> inside single quotes
//	DOUBLE_QUOTE -> inside double quotes
void	update_quote_state(char c, t_quote *quote_state)
{
	if (c == '\"')
	{
		if (*quote_state == DOUBLE_QUOTE)
			*quote_state = NO_QUOTE;
		else if (*quote_state == NO_QUOTE)
			*quote_state = DOUBLE_QUOTE;
	}
	else if (c == '\'')
	{
		if (*quote_state == SINGLE_QUOTE)
			*quote_state = NO_QUOTE;
		else if (*quote_state == NO_QUOTE)
			*quote_state = SINGLE_QUOTE;
	}
}