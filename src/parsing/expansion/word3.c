/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 04:16:53 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 04:16:54 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	generate_base_tokens(t_token *curr, t_shell *shell)
{
	t_token	*new;
	t_token	*first;
	t_token	*prev;
	int		index;
	int		len;

	first = NULL;
	prev = NULL;
	index = 0;
	while (curr->expanded[index] != '\0')
	{
		len = calc_token_size(curr, &index);
		new = make_base_token(curr, index - len, len, shell);
		if (!first)
			first = new;
		if (prev != NULL)
		{
			prev->next = new;
			new->prev = prev;
		}
		prev = new;
	}
	splice_token(curr, first, prev, shell);
}

t_token	*make_split_token(t_token *src, int start, int len, t_shell *shell)
{
	t_token	*new;
	int		i;

	new = (t_token *)arena_push(shell->arena, sizeof(t_token), 0, shell);
	new->type = TOKEN_WORD;
	new->is_expanded = true;
	new->value = src->value;
	new->expanded = (char *)arena_push(shell->arena, len + 1, 0, shell);
	new->ws_mask = NULL;
	i = 0;
	while (i < len)
	{
		new->expanded[i] = src->expanded[start + i];
		i++;
	}
	new->expanded[len] = '\0';
	return (new);
}

int	next_split_length(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && !is_ifs(str[len]))
	{
		len++;
	}
	return (len);
}
