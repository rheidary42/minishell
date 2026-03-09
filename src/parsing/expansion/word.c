/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:32:51 by rheidary          #+#    #+#             */
/*   Updated: 2026/02/02 20:06:52 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TO-DO*/
/*NOTES:
	Calculate minimum amount of tokens -> hi$var"var"/00111000 = 3 tokens min
	Make new tokens for every swap amount i.e. for every swap between 0 and 1
	
	Out of resulting tokens find the ones containing ws_mask
	Split the value saving it inside of a str array
	Make tokens out of the str array


	Modules:
	Layer 1 - Analysis
	Layer 2 - Slice extraction
	Layer 3 - Token creation
	Layer 4 - List replacement
	*/

void	split_token_segments_helper(t_token *new, t_token *prev)
{
	prev->next = new;
	new->prev = prev;
}

t_token	*split_token_segments(t_token *token, t_shell *shell,
		t_token *first, t_token *prev)
{
	t_token	*new;
	int		index;
	int		len;

	index = 0;
	while (token->expanded[index] != '\0')
	{
		while (token->expanded[index] != '\0' && is_ifs(token->expanded[index]))
			index++;
		if (token->expanded[index] == '\0')
			break ;
		len = next_split_length(token->expanded + index);
		new = make_split_token(token, index, len, shell);
		if (!first)
			first = new;
		if (prev)
			split_token_segments_helper(new, prev);
		prev = new;
		index += len;
		while (token->expanded[index] != '\0' && is_ifs(token->expanded[index]))
			index++;
	}
	return (first);
}

void	split_value(t_token *token, t_shell *shell)
{
	t_token	*first;
	t_token	*last;

	first = split_token_segments(token, shell, NULL, NULL);
	if (!first)
		return ;
	last = first;
	while (last->next)
	{
		last = last->next;
	}
	splice_token(token, first, last, shell);
}

bool	is_whitespace_token(t_token *curr)
{
	int		i;
	char	*value;

	value = curr->expanded;
	i = 0;
	while (value[i] != '\0')
	{
		if (curr->ws_mask[i] == false)
			return (false);
		i++;
	}
	return (true);
}

void	word(t_shell *shell)
{
	t_token	*curr;
	t_token	*next;

	curr = shell->tokens;
	while (curr != NULL)
	{
		next = curr->next;
		if (curr->type == TOKEN_WORD && curr->is_expanded == true
			&& needs_splitting(curr) == true)
		{
			generate_base_tokens(curr, shell);
		}
		curr = next;
	}
	curr = shell->tokens;
	while (curr != NULL)
	{
		next = curr->next;
		if (curr->type == TOKEN_WORD && curr->is_expanded == true
			&& curr->ws_mask != NULL)
		{
			split_value(curr, shell);
		}
		curr = next;
	}
}
