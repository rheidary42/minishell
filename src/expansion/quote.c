/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:32:37 by rheidary          #+#    #+#             */
/*   Updated: 2026/01/09 16:36:19 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	needs_removal(t_token *token, t_shell *shell)
{
	size_t	i;
	char	*str;

	if (token->type != TOKEN_WORD)
		return (false);
	if (token->is_expanded == true)
		str = token->expanded;
	else
		str = token->value;
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
	dest = (char *)arena_push(shell->arena, ft_strlen(value) + 1, 0);
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
		if (needs_removal(current, shell) == true)
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
		}
		current = current->next;
	}
}
