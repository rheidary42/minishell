/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:20:57 by rheidary          #+#    #+#             */
/*   Updated: 2026/01/05 19:22:09 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (is_expandable_var(token->value, i, NO_QUOTE))
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

size_t	calc_expanded_size(char *value, t_shell *shell)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' && ++i && ++len)
		{
			while (value[i] != '\0' && value[i] != '\'' && i++)
				len++;
			i++;
			len++;
		}
		else if (is_expandable_var(value, i, NO_QUOTE) && ++i)
			len += get_var_len(value, &i, shell);
		else if (++i)
			len++;
	}
	return (len);
}
