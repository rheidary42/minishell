/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:53:58 by rheidary          #+#    #+#             */
/*   Updated: 2026/02/05 14:05:40 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! Handle itoa failure in all cases in better way -> potentioally remake itoa to use arena
// ! Handle readline failure
// ! Handle syntax errors properly -> currently exits directly

void	full_exit(t_shell *shell)
{
	rl_clear_history();
	if (shell->arena)
		free(shell->arena);
	if (shell->env)
		free_env(&shell->env);
	if (shell->line)
		free(shell->line);
	if (shell)
		free(shell);
}

t_shell	*init_shell(t_shell *shell, char **envp)
{
	t_mem_arena	*arena;

	shell = ft_calloc(1, sizeof(t_shell));
	if (shell == NULL)
		return (NULL);
	shell->env = ft_calloc(1, sizeof(t_env));
	if (copy_envp(shell, shell->env, envp) == 1)
	{
		free(shell);
		return (NULL);
	}
	arena = arena_create(67 * KIB);
	if (arena == NULL)
	{
		perror("Arena alloaction failed\n");
		free_env(&shell->env);
		free(shell);
		return (NULL);
	}
	shell->arena = arena;
	shell->last_exit_status = 0;
	shell->line = NULL;
	shell->cmds = NULL;
	shell->tokens = NULL;
	return (shell);
}

char	*read_line_input(t_shell *shell, char *prev_line)
{
	char	*tmp;
	char	*line;

	if (prev_line)
	{
		free (prev_line);
		prev_line = NULL;
	}
	if (shell->is_interactive == true)
	{
		line = readline("minishell>");
		if (line && line[0] != '\0')
			add_history(line);
		return (line);
	}
	tmp = get_next_line(fileno(stdin));
	if (!tmp)
		return (NULL);
	line = ft_strtrim(tmp, "\n");
	free(tmp);
	return (line);
}

t_env	*find_node(t_env *env)
{
	t_env	*last;

	while (env != NULL)
	{
		last = env;
		if (env->name != NULL && ft_strcmp(env->name, "SHLVL") == 0)
			return (env);
		env = env->next;
	}
	return (last);
}

int	set_shlvl(t_shell *shell)
{
	t_env	*shlvl_node;
	char	*shlvl;
	int		shlvl_int;

	shlvl = getenv("SHLVL");
	shlvl_node = find_node(shell->env);
	if (shlvl == NULL || is_num(shlvl) == 0)
		return (add_env_var(shell, shlvl_node, "SHLVL", "1"));
	if (ft_strcmp(shlvl, "-1") == 0)
		return (add_env_var(shell, shlvl_node, "SHLVL", "0"));
	shlvl_int = ft_atol(shlvl);
	if (shlvl_int == -1)
		return (add_env_var(shell, shlvl_node, "SHLVL", "1"));
	if (shlvl_int < 0)
		return (add_env_var(shell, shlvl_node, "SHLVL", "0"));
	else
	{
		shlvl = ft_itoa(++shlvl_int);
		add_env_var(shell, shlvl_node, "SHLVL", shlvl);
		free(shlvl);
		return (0);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void)ac; (void)av;
	shell = init_shell(shell, envp);
	if (shell == NULL)
		return (EXIT_FAILURE);
	if (isatty(fileno(stdin)) == true)
		shell->is_interactive = 1;
	else
		shell->is_interactive = 0;
	setup_signals(shell);
	rl_event_hook = rl_ev_hook;
	if (set_shlvl(shell) == 1)
	{
		full_exit(shell);
		exit(1);
	}
	while (true)
	{
		shell->line = read_line_input(shell, shell->line);
		if (shell->line == NULL)    // If EOF (CTRL-D) detected exit
		{
			full_exit(shell);
			exit(0);
		}
		if (g_sig)
		{
			g_sig = 0;
			shell->last_exit_status = 130;
			continue ;
		}
		if (parse(shell) == EXIT_SUCCESS)
			execution(shell);
		arena_clear(shell->arena);
		g_sig = 0;
		shell->cmds = NULL;
		shell->tokens = NULL;
	}
	full_exit(shell);
	return (0);
}
