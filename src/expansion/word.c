/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:32:51 by rheidary          #+#    #+#             */
/*   Updated: 2026/01/06 16:16:04 by rheidary         ###   ########.fr       */
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

// Check for any occurence of ws_mask

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

int	calc_token_size(t_token *token, int *index)
{
	int		i;
	int		pos;
	bool	state;

	i = 0;
	pos = *index;
	state = token->ws_mask[pos];
	while (token->expanded[pos + i] != '\0' && token->ws_mask[pos + i] == state)
	{
		i++;
	}
	if ((pos + i > 0 && token->expanded[pos + i] != '\0')
		&& is_ifs(token->expanded[pos + i]) == true
		&& is_ifs(token->expanded[pos + i - 1]) == false)
	{
		while (token->expanded[pos + i] != '\0'
			&& is_ifs(token->expanded[pos + i]) == false)
		{
			i++;
		}
	}
	*index += i;
	return (i);
}

t_token	*make_base_token(t_token *src, int start, int len, t_shell *shell)
{
	t_token	*new;
	int		i;

	new = (t_token *)arena_push(shell->arena, sizeof(t_token), 0);
	new->type = TOKEN_WORD;
	new->is_expanded = true;
	new->value = src->value;
	new->expanded = (char *)arena_push(shell->arena, len + 1, 0);
	new->ws_mask = (bool *)arena_push(shell->arena, len, 0);
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

	new = (t_token *)arena_push(shell->arena, sizeof(t_token), 0);
	new->type = TOKEN_WORD;
	new->is_expanded = true;
	new->value = src->value;
	new->expanded = (char *)arena_push(shell->arena, len + 1, 0);
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

// Unfortunetaley hacky solution to save lines
// first and prev assigned in signature
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
		{
			prev->next = new;
			new->prev = prev;
		}

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
			&& curr->ws_mask != NULL && is_whitespace_token(curr))
		{
			split_value(curr, shell);
		}
		curr = next;
	}
}
