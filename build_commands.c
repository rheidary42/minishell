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

/* FOR CREATE_APPEND, safe calloc at end because, incase of argv failure, 
safe_calloc can only free "new". if its part of shell->cmds
same in append_redir, for redirection->file and
also refactored ft_strdup to use safe_calloc as well*/

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

t_cmd	*create_append(t_shell **shell, t_token *curr_token)
{
	t_cmd	*new;
	t_cmd	*curr;

	new = safe_calloc(sizeof(t_cmd), *shell);
	if ((*shell)->cmds == NULL)
	{
		(*shell)->cmds = new;
		return (new);
	}
	curr = (*shell)->cmds;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	new->argv = safe_calloc((count_argc(curr_token) + 1)
				* sizeof(char *), *shell);
	return (new);
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

void	append_redir(t_cmd *cmd, t_token *token, t_shell *shell)
{
	t_redir	*redirection;
	t_redir	*curr;

	redirection = safe_calloc(sizeof(t_redir), shell);
	if (redirection == NULL)
		return ; // TO DO ERROR
	redirection->type = token->type;
	redirection->prev = NULL;
	redirection->next = NULL;
	if (cmd->redir == NULL)
	{
		cmd->redir = redirection;
		return ;
	}
	curr = cmd->redir;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = redirection;
	redirection->prev = curr;
	redirection->file = ft_strdup(token->next->value, shell);
}
void	handle_redir(t_cmd *curr_cmd, t_token **curr_token_ptr, t_shell *shell)
{
	t_token	*curr_token;

	curr_token = *curr_token_ptr;
	if (curr_token->next != NULL && curr_token->next->type == TOKEN_WORD)
		{
			append_redir(curr_cmd, curr_token, shell);
			*curr_token_ptr = curr_token->next;
		}
}

void	build_commands(t_shell **shell)
{
	t_token	*curr;
	t_cmd	*cmd;
	int		i;

	i = 0;
	curr = (*shell)->tokens;
	cmd = NULL;
	while (curr != NULL)
	{
		if (cmd == NULL)
		{
			cmd = create_append(shell, curr);
			i = 0;
		}
		if (is_redir(curr) == true)
			handle_redir(cmd, &curr, *shell);
		else if (curr->type == TOKEN_WORD && is_argv(curr) == true)
			cmd->argv[i++] = curr->value;
		else if (curr->type == TOKEN_PIPE)
		{
			if (cmd != NULL)
				cmd->argv[i] = NULL;
			cmd = NULL;
		}
		curr = curr->next;
	}
	if (cmd != NULL)
		cmd->argv[i] = NULL; // FOR THE LAST COMMANDS ARGV ARRAY
}
