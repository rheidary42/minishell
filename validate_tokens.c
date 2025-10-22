/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:16:17 by rheidary          #+#    #+#             */
/*   Updated: 2025/10/22 15:39:03 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//❌ Invalid patterns:

// Pipe at start or end:
// | ls
// ls |
//
// Two pipes in a row:
// ls || wc
//
// Redirection without a target:
// echo > 
// cat <
// ls >> |
//
// Two redirections in a row (unless second is << or >> as part of token):
// echo > < file
//
// Only EOF or empty input:
// should be handled by main

int	is_redir(t_token *tok)
{
	return (tok->type == TOKEN_REDIR_OUT || tok->type == TOKEN_REDIR_IN
		|| tok->type == TOKEN_APPEND || tok->type == TOKEN_HEREDOC);
}

int	is_pipe(t_token *token)
{
	return (token->type == TOKEN_PIPE);
}

int	validate_tokens(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	if (is_pipe(curr))
		return (0);
	while (curr)
	{
		if (is_pipe(curr) != 0)
		{
			if (curr->next == NULL || is_pipe(curr->next) != 0)
				return (0);
		}
		else if (is_redir(curr) != 0)
		{
			if (curr->next == NULL || curr->next->type != TOKEN_WORD)
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}
