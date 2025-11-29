/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 20:23:59 by rheidary          #+#    #+#             */
/*   Updated: 2025/11/28 16:53:06 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_var_len(char *value, int *var_start, t_shell *shell)
{
	char	*var_name;
	int		var_end;
	t_env	*head;
	size_t	len;

	len = 0;
	var_end = *var_start;
	if (value[*var_start] == '?')
		return (*var_start += 1, exit_status_len(shell->last_exit_status));
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
		//test'hi'
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
		// INFO: '_' only in POSIX implementations -> Fuck it (?)
		if ((token->value[i] == '$' && ft_isalpha(token->value[i + 1]))
			|| (token->value[i] == '$' && token->value[i + 1] == '?'))
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

void	insert_exit_status(t_token *token, t_shell *shell)
{
	return ;
}

void	handle_var(size_t *i, int *in_quote, t_token *token, t_shell *shell)
{
	char	*var_value;
	size_t	var_len;
	size_t	j;

	if (*in_quote != 2)
		i[0]++;
	if (token->value[i[0]] == '?')
	{
		insert_exit_status(token, shell);
		i[0]++;
		return ;
	}
	var_value = get_var_value(get_var_name(token->value, &i[0]), shell);
	if (!var_value)
		return ;
	j = 0;
	var_len = ft_strlen(var_value);
	while (j < var_len)
	{
		copy_char_expansion(i, token->expanded, var_value[j]);
		j++;
	}
	free(var_value);
}

void	copy_char_expansion(size_t *i, char *dest, char c)
{
	dest[i[1]] = c;
	i[1]++;
}

void	copy_char_original(size_t *i, int *in_quote, t_token *token)
{
	if (token->value[i[0]] == '\"' && *in_quote == 1)
		*in_quote = 0;
	else if (token->value[i[0]] == '\"')
		*in_quote = 1;
	if (token->value[i[0]] == '\'' && *in_quote == 2)
		*in_quote = 0;
	else if (token->value[i[0]] == '\'')
		*in_quote = 2;
	if (*in_quote == 1)
		token->dq_mask[i[1]] = true;
	else
		token->dq_mask[i[1]] = false;
	token->expanded[i[1]++] = token->value[i[0]++];
}

//	i[0] = tracking value
//	i[1] = tracking expanded value
//	in_quote = 1 -> double quotes
//	in_quote = 2 -> single quotes
//	A little unhinged but if i don't understand it in a week
//	and you don't understand it ever and the evaluator doesn't
//	even know what hes looking at, then we can't fail because
//	noone understands anything :5head:
void	expand_value(t_token *token, t_shell *shell, size_t len)
{
	int		in_quote;
	size_t	i[2];

	token->expanded = safe_calloc(len + 1, shell);
	token->dq_mask = safe_calloc(len, shell);
	// "$var"hi'$var'
	in_quote = 0;
	i[0] = 0;
	i[1] = 0;
	while (i[1] < len)
	{
		if (token->value[i[0]] == '$' && in_quote != 2
			&& (ft_isalpha(token->value[i[0] + 1])
				|| token->value[i[0] + 1] == '?'))
			handle_var(i, &in_quote, token, shell);
		else
			copy_char_original(i, &in_quote, token);
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
			expand_value(curr, shell,
				calc_expanded_size(curr->value, shell));
		}
		else
			curr->is_expanded = false;
		curr = curr->next;
	}
}

// ////////////////////////////////////

// void	word(t_shell *shell)
// {
	
// }

// ////////////////////////////////////

// void	quote(t_shell *shell)
// {
	
// }

// void	expand(t_shell *shell)
// {
// 	parameter(shell);
// 	word(shell);
// 	quote(shell);
// }


// === TESTER ===

/* Helper to create a new environment variable */
t_env *new_env(const char *name, const char *value)
{
    t_env *env = malloc(sizeof(t_env));
    if (!env)
        return NULL;
    env->name = strdup(name);
    env->value = strdup(value);
    env->next = NULL;
    return env;
}

/* Helper to add env to shell */
void add_env(t_shell *shell, t_env *env)
{
    if (!shell->env)
        shell->env = env;
    else
    {
        t_env *tmp = shell->env;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = env;
    }
}

/* Helper to create a new token */
t_token *new_token(const char *value)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = strdup(value);
    token->expanded = NULL;
    token->dq_mask = NULL;
    token->is_expanded = false;
    token->type = TOKEN_WORD;
    token->next = NULL;
    token->prev = NULL;
    return token;
}

/* Print expanded token values */
// void print_tokens(t_shell *shell)
// {
//     t_token *curr = shell->tokens;
//     while (curr)
//     {
//         printf("Original: [%s]\n", curr->value);
//         printf("Expanded: [%s]\n", curr->expanded ? curr->expanded : "(null)");
//         printf("Double-quote mask: ");
//         if (curr->dq_mask)
//         {
//             for (size_t i = 0; i < strlen(curr->expanded); i++)
//                 printf("%d", curr->dq_mask[i]);
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
//     shell.tokens = new_token("Hello $USER!");
//     shell.tokens->next = new_token("Your home is $HOME.");
// 	shell.tokens->next = new_token("\"User: $USER\"");

//     /* Run expansion */
//     parameter(&shell);

//     /* Print results */
//     print_tokens(&shell);

//     return 0;
// }