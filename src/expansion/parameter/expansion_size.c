/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:20:57 by rheidary          #+#    #+#             */
/*   Updated: 2026/01/09 23:01:23 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	needs_expansions(t_token *token)
{
	int		i;
	t_quote	quote_state;

	if (token->type != TOKEN_WORD || token->value == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (token->value[i])
	{
		update_quote_state(token->value[i], &quote_state);
		if (is_expandable_var(token->value, i, quote_state))
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

size_t	calc_expanded_size(char *value, t_shell *shell)
{
	size_t	len;
	int		i;
	t_quote	quote_state;

	len = 0;
	i = 0;
	quote_state = NO_QUOTE;
	while (value[i])
	{
		update_quote_state(value[i], &quote_state);
		if (value[i] == '\'' && quote_state == NO_QUOTE && ++i && ++len)
			continue ;
		if (is_expandable_var(value, i, quote_state) && ++i)
			len += get_var_len(value, &i, shell);
		else if (++i)
			len++;
	}
	return (len);
}
