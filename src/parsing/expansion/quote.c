/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:32:37 by rheidary          #+#    #+#             */
/*   Updated: 2026/02/17 18:18:31 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	just_quotes(char *str)
{
	if (str[0] == '\0' || str[1] == '\0')
		return (true);
	if ((str[0] == '\'' || str[0] == '"')
		&& (str[1] == '\'' || str[1] == '"'))
		return (true);
	return (false);
}

bool	needs_removal(t_token *token)
{
	size_t	i;
	char	*str;

	if (token->type != TOKEN_WORD)
		return (false);
	if (token->is_expanded == true)
		str = token->expanded;
	else
		str = token->value;
	if (just_quotes(str) == true)
		return (false);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

char	*remove_quotes(char *value, t_shell *shell)
{
	size_t	i;
	size_t	j;
	char	*dest;
	t_quote	quote_state;

	quote_state = NO_QUOTE;
	dest = (char *)arena_push(shell->arena, ft_strlen(value) + 1, 0, shell);
	i = 0;
	j = 0;
	while (value[i] != '\0')
	{
		update_quote_state(value[i], &quote_state);
		if (quote_state == DOUBLE_QUOTE && value[i] == '\'')
			dest[j++] = value[i];
		if (quote_state == SINGLE_QUOTE && value[i] == '\"')
			dest[j++] = value[i];
		if (value[i] != '\"' && value[i] != '\'')
			dest[j++] = value[i];
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

void	quote_removal(t_shell *shell)
{
	t_token	*current;
	char	*new_str;

	current = shell->tokens;
	while (current != NULL)
	{
		if (needs_removal(current) == true)
		{
			if (current->is_expanded == true)
			{
				new_str = remove_quotes(current->expanded, shell);
				current->expanded = new_str;
			}
			else
			{
				new_str = remove_quotes(current->value, shell);
				current->value = new_str;
			}
			current->was_quoted = true;
		}
		current = current->next;
	}
}
