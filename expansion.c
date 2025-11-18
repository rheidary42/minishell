/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 20:23:59 by rheidary          #+#    #+#             */
/*   Updated: 2025/11/18 17:59:49 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_var_len(char *value, int *i, t_shell *shell)
{
	
}

size_t	calc_expanded_size(char *value, t_shell *shell)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'')
		{
			i++;
			while (value[i] != '\0' && value[i] != '\'')
			{
				len++;
				i++;
			}
			i++;
			continue ;
		}
		else if (value[i] == '$')
			len += get_var_len(value, &i, shell);
		else
			len++;
	}
	return (len);
}

int	needs_expansions(t_token *token)
{
	int	i;

	if (token->type != TOKEN_WORD || token->value == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'')
		{
			i++;
			while (token->value[i] != '\'')
				i++;
			i++;
			if (token->value[i] == '\0')
				return (EXIT_FAILURE);
		}
		if ((token->value[i] == '$' && ft_isalpha(token->value[i + 1]))
			|| (token->value[i] == '$' && token->value[i + 1] == '?'))
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

void	parameter(t_shell *shell)
{
	t_token	*curr;
	char	*new_value;

	curr = shell->tokens;
	while (curr != NULL)
	{
		if (needs_expansions(curr))
		{
			new_value = expand_value(curr->value,
					calc_expanded_size(curr->value, shell) + 1, shell);
			free(curr->value);
			curr->value = new_value;
		}
		curr = curr->next;
	}
}


////////////////////////////////////

void	word(t_shell *shell)
{
	
}

////////////////////////////////////

void	quote(t_shell *shell)
{
	
}

void	expand(t_shell *shell)
{
	parameter(shell);
	word(shell);
	quote(shell);
}
