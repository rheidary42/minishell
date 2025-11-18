/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 20:23:59 by rheidary          #+#    #+#             */
/*   Updated: 2025/11/18 21:42:00 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	exit_status_len(int i)
{
	if (i < 10)
		return (1);
	if (i < 100)
		return (2);
	return (3);
}

int	ft_is_space(char c)
{
	return ()
}

size_t	get_var_len(char *value, int *i, t_shell *shell)
{
	char	*key;
	int		start;
	t_env	*head;
	size_t	len;

	len = 0;
	start = *i;
	if (value[*i] == '?')
		return (*i += 1, exit_status_len(shell->last_exit_status));
	while (value[start] && (ft_isalnum(value[start])) != 0)
		start++;
	key = ft_substr(value, *i, start - (*i + 1));
	head = shell->env;
	while (head != NULL)
	{
		if (ft_strcmp(head->name, key) == 0)
		{
			len = ft_strlen(head->value);
			break ;
		}
		head = head->next;
	}
	*i = start;
	return (free(key), len);
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
		}
		else if (value[i] == '$' && ++i)
			len += get_var_len(value, &i, shell);
		else if (++i)
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
		// Add '_' potentially, ask around and look in manual
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
