#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "minishell.h"

static t_env *test_new_env(const char *name, const char *value, t_shell *shell)
{
    t_env	*env;
    env = (t_env *)arena_push(shell->arena, sizeof(t_env), 0);
    env->name = arena_push(shell->arena, strlen(name) + 1, 0);
    env->value = arena_push(shell->arena, strlen(value) + 1, 0);
    strcpy(env->name, name);
    strcpy(env->value, value);
    env->next = NULL;
    return (env);
}

static void test_add_env(t_shell *shell, t_env *env)
{
	t_env *tmp;

	if (!shell->env)
	{
		shell->env = env;
		return;
	}
	tmp = shell->env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = env;
}

static t_token *test_new_token(const char *value, t_shell *shell)
{
	t_token *token;
	token = (t_token *)arena_push(shell->arena, sizeof(t_token), 0);
	token->value = arena_push(shell->arena, strlen(value) + 1, 0);
	strcpy(token->value, value);
	token->expanded = NULL;
	token->ws_mask = NULL;
	token->is_expanded = false;
	token->type = TOKEN_WORD;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

static void test_print_tokens(t_shell *shell)
{
	t_token *curr = shell->tokens;
	size_t i;
	int token_index = 0;

	while (curr)
	{
		printf("--- Token %d ---\n", token_index++);
		printf("Type     : %d\n", curr->type);
		printf("Original : [%s]\n", curr->value ? curr->value : "(null)");
		printf("Expanded : [%s]\n", curr->expanded ? curr->expanded : "(null)");
		printf("WS mask  : ");
		if (curr->ws_mask && curr->expanded)
		{
			i = 0;
			while (curr->expanded[i])
			{
				printf("%d", curr->ws_mask[i]);
				i++;
			}
		}
		else
			printf("(null)");
		printf("\n\n");
		curr = curr->next;
	}
}

int	main(void)
{
	t_shell	shell;
	t_token	*tokens[20];
	int		i = 0;

	memset(&shell, 0, sizeof(t_shell));
	shell.arena = arena_create(8192);

	test_add_env(&shell, test_new_env("VAR", "one two three", &shell));
	test_add_env(&shell, test_new_env("EMPTY", "", &shell));
	test_add_env(&shell, test_new_env("SPACED", "  hello  world  ", &shell));
	test_add_env(&shell, test_new_env("SINGLE", "word", &shell));
	test_add_env(&shell, test_new_env("TAB", "a\tb\tc", &shell));
	test_add_env(&shell, test_new_env("NEWLINE", "x\ny\nz", &shell));
	test_add_env(&shell, test_new_env("MIXED", " a\tb \nc ", &shell));
	test_add_env(&shell, test_new_env("PATH", "/usr/bin:/bin", &shell));
	test_add_env(&shell, test_new_env("USER", "hi", &shell));

	tokens[i++] = test_new_token("echo ''''$USER''''", &shell);
	tokens[i++] = test_new_token("$VAR", &shell);              // Basic: one two three
	tokens[i++] = test_new_token("$SINGLE", &shell);           // Single word: word
	tokens[i++] = test_new_token("$EMPTY", &shell);            // Empty expansion
	tokens[i++] = test_new_token("prefix$VAR", &shell);        // prefix one two three
	tokens[i++] = test_new_token("$VAR$VAR", &shell);          // one two three one two three
	tokens[i++] = test_new_token("a$VAR", &shell);             // a one two three (short prefix)
	tokens[i++] = test_new_token("hi$SPACED", &shell);         // Leading/trailing spaces with prefix
	tokens[i++] = test_new_token("$SPACED", &shell);           // Leading/trailing spaces
	tokens[i++] = test_new_token("x$EMPTY", &shell);           // x (empty var in middle)
	tokens[i++] = test_new_token("$EMPTY$EMPTY", &shell);      // Double empty
	tokens[i++] = test_new_token("$TAB", &shell);              // Tab splitting: a b c
	tokens[i++] = test_new_token("$NEWLINE", &shell);          // Newline splitting: x y z
	tokens[i++] = test_new_token("$MIXED", &shell);            // Mixed IFS chars: a b c
	tokens[i++] = test_new_token("$PATH", &shell);             // No split (no IFS): /usr/bin:/bin
	tokens[i++] = test_new_token("$VAR$SINGLE", &shell);       // one two three word
	tokens[i++] = test_new_token("$SINGLE$VAR$SINGLE", &shell); // word one two three word

	// Link all tokens
	shell.tokens = tokens[0];
	for (int j = 0; j < i - 1; j++)
	{
		tokens[j]->next = tokens[j + 1];
		tokens[j + 1]->prev = tokens[j];
	}


	printf("=== Initial tokens ===\n\n");
	test_print_tokens(&shell);

	// Run parameter expansion (you need to implement or mock this)
	parameter(&shell);

	printf("=== After parameter expansion ===\n\n");
	test_print_tokens(&shell);

	// Run word splitting
	word(&shell);

	printf("=== After word splitting ===\n\n");
	test_print_tokens(&shell);

	// Print summary
	printf("=== SUMMARY ===\n");
	t_token *curr = shell.tokens;
	int	token_count = 0;
	while (curr)
	{
		token_count++;
		curr = curr->next;
	}
	printf("Total tokens after splitting: %d\n", token_count);
	return (0);
}