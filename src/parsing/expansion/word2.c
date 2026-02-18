/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 04:16:50 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/18 03:40:35 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	needs_splitting(t_token *curr)
{
	int		i;
	char	*value;

	i = 0;
	value = curr->expanded;
	while (value[i] != '\0')
	{
		if (curr->ws_mask[i] == true)
			return (true);
		i++;
	}
	return (false);
}

int	calc_new_token_size(t_token *token, int *index)
{
	int		i;
	int		pos;
	int		leading_space_offset;
	bool	state;

	i = 0;
	pos = *index;
	leading_space_offset = 0;
	state = token->ws_mask[pos];
	while (token->expanded[pos + i] != '\0' && token->ws_mask[pos + i] == state
		&& is_ifs(token->expanded[pos + i])
		&& !(is_ifs(token->expanded[pos + i + 1])) && leading_space_offset++)
		i++;
	while (token->expanded[pos + i] != '\0' && token->ws_mask[pos + i] == state)
		i++;
	if ((pos + i > 0 && token->expanded[pos + i] != '\0')
		&& is_ifs(token->expanded[pos + i]) == false)
	{
		while (token->expanded[pos + i] != '\0'
			&& is_ifs(token->expanded[pos + i]) == false)
			i++;
	}
	*index += i;
	return (i - leading_space_offset);
}

t_token	*make_base_token(t_token *src, int start, int len, t_shell *shell)
{
	t_token	*new;
	int		i;

	new = (t_token *)arena_push(shell->arena, sizeof(t_token), 0, shell);
	new->type = TOKEN_WORD;
	new->is_expanded = true;
	new->value = src->value;
	new->expanded = (char *)arena_push(shell->arena, len + 1, 0, shell);
	new->ws_mask = (bool *)arena_push(shell->arena, len, 0, shell);
	i = 0;
	while (i < len)
	{
		new->expanded[i] = src->expanded[start + i];
		new->ws_mask[i] = src->ws_mask[start + i];
		i++;
	}
	new->expanded[i] = '\0';
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

// Link new tokens in place of the old one
void	splice_token(t_token *old, t_token *first, t_token *last,
		t_shell *shell)
{
	t_token	*prev;
	t_token	*next;

	prev = old->prev;
	next = old->next;
	if (prev)
		prev->next = first;
	else
		shell->tokens = first;
	first->prev = prev;
	if (next)
		next->prev = last;
	last->next = next;
}
