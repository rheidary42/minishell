/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 20:23:59 by rheidary          #+#    #+#             */
/*   Updated: 2025/11/04 18:05:39 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_connection()
{
	
}

int	find_var(t_shell *shell)
{
	t_token	*curr;

	curr = shell->tokens;
	while (shell->tokens != NULL)
	{
		if (match_connection(curr->value))
			
	}
}

void	do_expansion(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->tokens->value[i] != '\0')
	{
		if (shell->tokens->value[i] == '$')
		{
			find_var(shell);
			i = 0;
		}
		i++;
	}
}

int	needs_expansions(t_token *token)
{
	int	i;

	if (token->type != TOKEN_WORD || token->value == NULL)
		return (0);
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'')
		{
			i++;
			while (token->value[i] != '\'')
				i++;
		}
		if (token->value[i] == '$' && ft_isalpha(token->value[i + 1]
				|| token->value[i + 1] == '?'))
			return (1);
	}
	return (0);
}

void	parameter(t_shell *shell)
{
	t_token	*curr;

	curr = shell->tokens;
	while (curr != NULL)
	{
		if (needs_expansions(shell->tokens))
			do_expansion(shell);
		curr = curr->next;
	}
}

void	expand(t_shell *shell)
{
	parameter(shell);
	word();
	quote();
}
