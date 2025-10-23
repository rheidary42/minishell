/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:10:30 by rheidary          #+#    #+#             */
/*   Updated: 2025/10/22 14:22:35 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_argc(t_token **tokens)
{
	t_token	*curr;
	int		count;

	count = 0;
	curr = *tokens;
	while (curr->type != TOKEN_PIPE)
	{
		curr = curr->next;
		count++;
	}
	return (count);
}

t_cmd	*new_cmd_node(t_cmd **cmds, t_token **tokens)
{
	t_cmd	*new;
	t_cmd	*curr;

	curr = *cmds;
	new = ft_calloc(1, sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->argv = malloc(sizeof(char *) * (count_argc(tokens) + 1));
	if (new->argv == NULL)
		return (NULL);
	if (*cmds == NULL)
	{
		*cmds = new;
		return (new);
	}
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	return(curr->next);
}

void	build_commands(t_cmd **cmds, t_token **tokens)
{
	t_token	*token_curr;
	t_cmd	*cmd_curr;
	int		i;

	i = 0;
	token_curr = *tokens;
	cmd_curr = *cmds;
	while (token_curr->next != NULL)
	{
		// build_argv(cmds, tokens);
		// build_redir();
		if (cmd_curr == NULL || token_curr->type == TOKEN_PIPE)
		{
			cmd_curr = new_cmd_node(cmds, tokens);
			if (cmd_curr == NULL)
				return ; //to do error handling
			i = 0;
			token_curr = token_curr->next;
		}
		if (token_curr->type == TOKEN_HEREDOC)
		{
			cmd_curr->redir->type = TOKEN_HEREDOC;
			cmd_curr->redir->file = token_curr->next->value;
			token_curr = token_curr->next->next;
		}
		else if (token_curr->type == TOKEN_REDIR_OUT
				&& token_curr->next->type == TOKEN_WORD)
		{
			cmd_curr->redir->type = TOKEN_REDIR_OUT;
			cmd_curr->redir->file = token_curr->next->value;
			token_curr = token_curr->next->next;
		}
		else if (token_curr->type == TOKEN_REDIR_IN
				&& token_curr->prev->type == TOKEN_WORD)
		{
			cmd_curr->redir->type = TOKEN_REDIR_IN;
			cmd_curr->redir->file = token_curr->prev->value;
			token_curr = token_curr->next;
		}
		else if (token_curr->type == TOKEN_WORD)
		{
			cmd_curr->argv[i] = token_curr->value;
			token_curr = token_curr->next;
			i++;
		}
	}
}