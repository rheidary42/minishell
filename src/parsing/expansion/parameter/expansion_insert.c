/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:22:19 by rheidary          #+#    #+#             */
/*   Updated: 2026/01/09 23:18:18 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_exit_status(t_pos *pos, t_token *token, t_shell *shell)
{
	char	*exit_status;
	int		exit_len;
	int		i;

	exit_status = ft_itoa(shell->last_exit_status);
	if (exit_status == NULL)
		clean_up(shell);
	exit_len = exit_status_len(shell->last_exit_status);
	i = -1;
	while (++i < exit_len)
	{
		token->expanded[pos->exp + i] = exit_status[i];
	}
	pos->exp += exit_len;
	free(exit_status);
}

void	handle_var(t_pos *pos, t_quote *quote_state,
			t_token *token, t_shell *shell)
{
	char	*var_value;
	size_t	var_len;
	size_t	j;

	if (*quote_state != SINGLE_QUOTE)
		pos->org++;
	if (token->value[pos->org] == '?')
	{
		insert_exit_status(pos, token, shell);
		pos->org++;
		return ;
	}
	var_value = get_var_value(get_var_name(shell,
				token->value, &pos->org), shell);
	if (!var_value)
		return ;
	j = 0;
	var_len = ft_strlen(var_value);
	while (j < var_len)
	{
		token->expanded[pos->exp] = var_value[j];
		token->ws_mask[pos->exp] = (*quote_state == NO_QUOTE);
		pos->exp++;
		j++;
	}
}
