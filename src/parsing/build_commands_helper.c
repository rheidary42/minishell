/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 04:01:32 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 04:01:33 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_argc(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens != NULL && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

void	finish_argv(t_cmd **cmd, int *i)
{
	t_cmd	*c;
	int		j;

	j = *i;
	c = *cmd;
	if (c != NULL)
		c->argv[j] = NULL;
	*cmd = NULL;
}

bool	is_redir(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
	{
		return (true);
	}
	return (false);
}

bool	is_argv(t_token *token)
{
	if (token->prev == NULL || is_redir(token->prev) == false)
		return (true);
	return (false);
}
