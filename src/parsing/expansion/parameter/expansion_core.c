/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:23:18 by rheidary          #+#    #+#             */
/*   Updated: 2026/02/02 20:04:30 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Copy characters from token->value to token->expanded, expanding $vars
//	pos.org = index in token->value
//	pos.exp = index in token->expanded
void	expand_value(t_token *token, t_shell *shell, size_t len)
{
	t_quote			quote_state;
	t_pos			pos;

	token->expanded = (char *)arena_push(shell->arena, len + 1, 0, shell);
	token->ws_mask = (bool *)arena_push(shell->arena, len, 0, shell);
	quote_state = NO_QUOTE;
	pos.org = 0;
	pos.exp = 0;
	while (pos.exp < len)
	{
		if (is_expandable_var(token->value, pos.org, quote_state))
			handle_var(&pos, &quote_state, token, shell);
		else
		{
			update_quote_state(token->value[pos.org], &quote_state);
			token->expanded[pos.exp++] = token->value[pos.org++];
		}
	}
}

void	parameter(t_shell *shell)
{
	t_token	*curr;

	curr = shell->tokens;
	while (curr != NULL)
	{
		if (needs_expansions(curr) == EXIT_SUCCESS)
		{
			curr->is_expanded = true;
			expand_value(curr, shell, calc_expanded_size(curr->value, shell));
		}
		else
		{
			curr->is_expanded = false;
			curr->expanded = NULL;
			curr->ws_mask = NULL;
		}
		curr = curr->next;
	}
}
