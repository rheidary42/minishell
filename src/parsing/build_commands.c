/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:10:30 by rheidary          #+#    #+#             */
/*   Updated: 2026/02/02 20:05:36 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* FOR CREATE_APPEND, safe calloc at end because, incase of argv failure, 
safe_calloc can only free "new". if its part of shell->cmds
same in append_redir, for redirection->file and
also refactored ft_strdup to use safe_calloc as well*/
// ! OUTDATED COMMENT - arena allocation used throughout

#include "minishell.h"

t_cmd	*create_append(t_shell *shell, t_token *curr_token, int *i)
{
	t_cmd	*new;
	t_cmd	*curr;

	new = (t_cmd *)arena_push(shell->arena, sizeof(t_cmd), 0, shell);
	*i = 0;
	if (shell->cmds == NULL)
	{
		shell->cmds = new;
		new->argv = (char **)arena_push(shell->arena,
				(count_argc(curr_token) + 1) * sizeof(char *), 0, shell);
		return (new);
	}
	curr = shell->cmds;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	new->argv = (char **)arena_push(shell->arena, (count_argc(curr_token) + 1)
			* sizeof(char *), 0, shell);
	return (new);
}

void	append_redir(t_cmd *cmd, t_token *token, t_shell *shell)
{
	t_redir	*redirection;
	t_redir	*curr;

	redirection = (t_redir *)arena_push(shell->arena,
			sizeof(t_redir), 0, shell);
	redirection->type = token->type;
	redirection->was_quoted = token->next->was_quoted;
	redirection->file = (char *)arena_push(shell->arena,
			ft_strlen(token->next->value) + 1, 0, shell);
	ft_strlcpy(redirection->file, token->next->value,
		ft_strlen(token->next->value) + 1);
	redirection->next = NULL;
	if (cmd->redir == NULL)
	{
		cmd->redir = redirection;
		redirection->prev = NULL;
		return ;
	}
	curr = cmd->redir;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = redirection;
	redirection->prev = curr;
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

void	build_commands(t_shell *shell)
{
	t_token	*curr;
	t_cmd	*cmd;
	int		i;

	i = 0;
	curr = shell->tokens;
	cmd = NULL;
	while (curr != NULL)
	{
		if (cmd == NULL)
			cmd = create_append(shell, curr, &i);
		if (is_redir(curr) == true)
			handle_redir(cmd, &curr, shell);
		else if (curr->type == TOKEN_WORD && is_argv(curr) == true
			&& curr->is_expanded == false)
			cmd->argv[i++] = curr->value;
		else if (curr->type == TOKEN_WORD && is_argv(curr) == true
			&& curr->is_expanded == true)
			cmd->argv[i++] = curr->expanded;
		else if (curr->type == TOKEN_PIPE)
			finish_argv(&cmd, &i);
		curr = curr->next;
	}
	if (cmd != NULL)
		cmd->argv[i] = NULL;
}
