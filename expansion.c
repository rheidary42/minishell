/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 20:23:59 by rheidary          #+#    #+#             */
/*   Updated: 2025/12/16 22:39:59 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* Modularity, keep scalable. Have crates that can be handled appropriately.
   Handle issues appropriately*/
//	Calculate the length of the variable's value for expansion
size_t	get_var_len(char *value, int *var_start, t_shell *shell)
{
	char	*var_name;
	int		var_end;
	t_env	*head;
	size_t	len;

	len = 0;
	if (value[*var_start] == '?')
		return (*var_start += 1, exit_status_len(shell->last_exit_status));
	var_end = *var_start;
	while (value[var_end] && (ft_isalnum(value[var_end])) != 0)
		var_end++;
	var_name = ft_substr(value, *var_start, var_end - *var_start);
	head = shell->env;
	while (head != NULL)
	{
		if (ft_strcmp(head->name, var_name) == 0)
		{
			len = ft_strlen(head->value);
			break ;
		}
		head = head->next;
	}
	*var_start = var_end;
	return (free(var_name), len);
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

// Add '_' potentially, ask around and look in manual
// INFO: '_' only in POSIX implementations -> Fuck it (?)
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

char	*get_var_value(char *var_name, t_shell *shell)
{
	t_env	*head;

	head = shell->env;
	while (head != NULL)
	{
		if (ft_strcmp(head->name, var_name) == 0)
		{
			free(var_name);
			return (ft_strdup(head->value));
		}
		head = head->next;
	}
	free(var_name);
	return (NULL);
}

char	*get_var_name(char *value, size_t *var_start)
{
	size_t	var_end;
	char	*var_name;

	var_end = *var_start;
	while (value[var_end] && (ft_isalnum(value[var_end])) != 0)
		var_end++;
	var_name = ft_substr(value, *var_start, var_end - *var_start);
	*var_start = var_end;
	return (var_name);
}

void	insert_exit_status(t_pos *pos, t_token *token, t_shell *shell,
			t_quote *quote_state)
{
	char	*exit_status;
	char	*dest;
	int		exit_len;
	int		i;

	exit_status = ft_itoa(shell->last_exit_status);
	if (exit_status == NULL)
		clean_up(shell);
	dest = shell->tokens->expanded + pos->exp;
	exit_len = exit_status_len(shell->last_exit_status);
	i = -1;
	while (++i < exit_len)
	{
		if (*quote_state == DOUBLE_QUOTE)
			token->ws_mask[pos->exp + i] = true;
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
		pos->val++;
	if (token->value[pos->val] == '?')
	{
		insert_exit_status(pos, token, shell, quote_state);
		pos->val++;
		return ;
	}
	var_value = get_var_value(get_var_name(token->value, &pos->val), shell);
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
	free(var_value);
}

//	Copy characters from token->value to token->expanded, expanding $vars
//	pos.val = index in token->value
//	pos.exp = index in token->expanded
void	expand_value(t_token *token, t_shell *shell, size_t len)
{
	t_quote			quote_state;
	t_pos			pos;

	token->expanded = safe_calloc(len + 1, shell);
	token->ws_mask = safe_calloc(len, shell);
	quote_state = NO_QUOTE;
	pos.val = 0;
	pos.exp = 0;
	while (pos.exp < len)
	{
		if (is_expandable_var(token->value, pos.val, quote_state))
			handle_var(&pos, &quote_state, token, shell);
		else
		{
			update_quote_state(token->value[pos.val], &quote_state);
			token->expanded[pos.exp++] = token->value[pos.val++];
		}
	}
}

void	parameter(t_shell *shell)
{
	t_token	*curr;

	curr = shell->tokens;
	while (curr != NULL)
	{
		if (needs_expansions(curr) == EXIT_SUCCESS)
		{
			curr->is_expanded = true;
			expand_value(curr, shell, calc_expanded_size(curr->value, shell));
		}
		else
		{
			curr->is_expanded = false;
			curr->expanded = NULL;
			curr->ws_mask = NULL;
		}
		curr = curr->next;
	}
}

// ////////////////////////////////////


/* TO-DO*/
/*NOTES:
	Calculate minimum amount of tokens -> hi$var"var"/00111000 = 3 tokens min
	Make new tokens for every swap amount i.e. for every swap between 0 and 1
	
	Out of resulting tokens find the ones containing ws_mask
	Split the value saving it inside of a str array
	Make tokens out of the str array


	Modules:
	Layer 1 - Analysis
	Layer 2 - Slice extraction
	Layer 3 - Token creation
	Layer 4 - List replacement
	*/

// Check for any occurence of ws_mask
bool	needs_splitting(t_token *curr)
{
	int		i;
	char	*value;

	i = 0;
	value = curr->expanded;
	while (value[i] != '\0')
	{
		if (curr->ws_mask[i] == true)
			return (true);
		i++;
	}
	return (false);
}

int	calc_token_size(t_token *token, int *index)
{
	int		i;
	int		pos;
	bool	state;

	i = 0;
	pos = *index;
	state = token->ws_mask[pos];
	while (token->expanded[pos + i] != '\0' && token->ws_mask[pos + i] == state)
	{
		i++;
	}
	*index += i;
	return (i);
}

t_token	*make_base_token(t_token *src, int start, int len, t_shell *shell)
{
	t_token	*new;
	int		i;

	new = safe_calloc(sizeof(t_token), shell);
	new->type = TOKEN_WORD;
	new->is_expanded = true;
	new->value = NULL;
	new->expanded = safe_calloc(len + 1, shell);
	new->ws_mask = safe_calloc(len, shell);
	i = 0;
	while (i < len)
	{
		new->expanded[i] = src->expanded[start + i];
		new->ws_mask[i] = src->ws_mask[start + i];
		i++;
	}
	new->expanded[i] = '\0';
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

// Link new tokens in place of the old one
void	splice_token(t_token *old, t_token *first, t_token *last,
		t_shell *shell)
{
	t_token	*prev;
	t_token	*next;

	prev = old->prev;
	next = old->next;
	if (prev)
		prev->next = first;
	else
		shell->tokens = first;
	first->prev = prev;
	if (next)
		next->prev = last;
	last->next = next;

	// ! Maybe move memory management out of splicing for better modularization
	free(old->value);
	free(old->expanded);
	free(old->ws_mask);
	free(old);
}

void	generate_base_tokens(t_token *curr, t_shell *shell)
{
	t_token	*new;
	t_token	*first;
	t_token	*prev;
	int		index;
	int		len;

	first = NULL;
	prev = NULL;
	index = 0;
	while (curr->expanded[index] != '\0')
	{
		len = calc_token_size(curr, &index);
		new = make_base_token(curr, index - len, len, shell);
		if (!first)
			first = new;
		if (prev != NULL)
		{
			prev->next = new;
			new->prev = prev;
		}
		prev = new;
	}
	splice_token(curr, first, prev, shell);
}

t_token	*make_split_token(t_token *src, int start, int len, t_shell *shell)
{
	t_token	*new;
	int		i;

	new = safe_calloc(sizeof(t_token), shell);
	new->type = TOKEN_WORD;
	new->is_expanded = true;
	new->value = NULL;
	new->expanded = safe_calloc(len + 1, shell);
	new->ws_mask = NULL;
	i = 0;
	while (i < len)
	{
		new->expanded[i] = src->expanded[start + i];
		i++;
	}
	new->expanded[len] = '\0';
	return (new);
}

bool	is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	next_split_length(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && !is_ifs(str[len]))
	{
		len++;
	}
	return (len);
}

// Unfortunetaley hacky solution to save lines
// first and prev assigned in signature
t_token	*split_token_segments(t_token *token, t_shell *shell,
		t_token *first, t_token *prev)
{
	t_token	*new;
	int		index;
	int		len;

	index = 0;
	while (token->expanded[index] != '\0')
	{
		len = next_split_length(token->expanded + index);
		new = make_split_token(token, index, len, shell);
		if (!first)
			first = new;
		if (prev)
		{
			prev->next = new;
			new->prev = prev;
		}

		prev = new;
		index += len;
		while (token->expanded[index] != '\0' && is_ifs(token->expanded[index]))
			index++;
	}
	return (first);
}

void	split_value(t_token *token, t_shell *shell)
{
	t_token	*first;
	t_token	*last;

	first = split_token_segments(token, shell, NULL, NULL);
	if (!first)
		return ;
	last = first;
	while (last->next)
	{
		last = last->next;
	}
	splice_token(token, first, last, shell);
}

void	word(t_shell *shell)
{
	t_token	*curr;
	t_token	*next;

	curr = shell->tokens;
	while (curr != NULL)
	{
		next = curr->next;
		if (curr->type == TOKEN_WORD && curr->is_expanded == true
			&& needs_splitting(curr) == true)
		{
			generate_base_tokens(curr, shell);
		}
		curr = next;
	}
	curr = shell->tokens;
	while (curr != NULL)
	{
		next = curr->next;
		if (curr->type == TOKEN_WORD && curr->is_expanded == true
			&& needs_splitting(curr) == true)
		{
			split_value(curr, shell);
		}
		curr = next;
	}
}

// ////////////////////////////////////

/* TO-DO*/
// void	quote(t_shell *shell)
// {
	
// }

///////////////////////////////////////

// void	expand(t_shell *shell)
// {
// 	parameter(shell);
// 	word(shell);
// 	quote(shell);
// }

/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////

// // === TESTER ===

// // /* Helper to create a new environment variable */
// t_env *new_env(const char *name, const char *value)
// {
//     t_env *env = malloc(sizeof(t_env));
//     if (!env)
//         return NULL;
//     env->name = strdup(name);
//     env->value = strdup(value);
//     env->next = NULL;
//     return env;
// }

// /* Helper to add env to shell */
// void add_env(t_shell *shell, t_env *env)
// {
//     if (!shell->env)
//         shell->env = env;
//     else
//     {
//         t_env *tmp = shell->env;
//         while (tmp->next)
//             tmp = tmp->next;
//         tmp->next = env;
//     }
// }

// /* Helper to create a new token */
// t_token *new_token(const char *value)
// {
//     t_token *token = malloc(sizeof(t_token));
//     if (!token)
//         return NULL;
//     token->value = strdup(value);
//     token->expanded = NULL;
//     token->ws_mask = NULL;
//     token->is_expanded = false;
//     token->type = TOKEN_WORD;
//     token->next = NULL;
//     token->prev = NULL;
//     return token;
// }

// /* Print expanded token values */
// void print_tokens(t_shell *shell)
// {
//     t_token *curr = shell->tokens;
//     while (curr)
//     {
//         printf("Original: [%s]\n", curr->value);
//         printf("Expanded: [%s]\n", curr->expanded ? curr->expanded : "(null)");
//         printf("Double-quote mask: ");
//         if (curr->ws_mask)
//         {
//             for (size_t i = 0; i < strlen(curr->expanded); i++)
//                 printf("%d", curr->ws_mask[i]);
//         }
//         printf("\n\n");
//         curr = curr->next;
//     }
// }

// int main(void)
// {
//     t_shell shell;
//     memset(&shell, 0, sizeof(shell));

//     /* Setup environment */
//     add_env(&shell, new_env("USER", "alice"));
//     add_env(&shell, new_env("HOME", "/home/alice"));
//     add_env(&shell, new_env("SHELL", "/bin/bash"));

//     shell.last_exit_status = 42;

//     /* Setup tokens */
// 		shell.tokens = new_token("Hello $USER!");
// 		shell.tokens->next = new_token("Your home is $HOME.");
// 		shell.tokens->next->next = new_token("\"User: $USER\"");
// 		shell.tokens->next->next->next = new_token("\"$USER\"$USER'$USER'");
// 		shell.tokens->next->next->next->next = new_token("$?'$?'\"$?\"");
// 		shell.tokens->next->next->next->next->next = new_token("$$'$'\"$$\"");

//     /* Run expansion */
//     parameter(&shell);

//     /* Print results */
//     print_tokens(&shell);

//     return 0;
// }
