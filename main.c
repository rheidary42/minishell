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
	shell->save_stdin = -1;
	shell->save_stdout = -1;
	shell->line = NULL;
	shell->cmds = NULL;
	shell->tokens = NULL;
	return (shell);
}

void	read_line_input(t_shell *shell, char *prev_line)
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
		shell->line = line;
		if (shell->line == NULL)
			full_exit(shell, shell->last_exit_status);
		return ;
	}
	tmp = get_next_line(fileno(stdin));
	line = ft_strtrim(tmp, "\n");
	free(tmp);
	shell->line = line;
	if (shell->line == NULL)
		full_exit(shell, shell->last_exit_status);
}

void	set_interactive_mode(t_shell *shell)
{
	if (isatty(fileno(stdin)) == true)
		shell->is_interactive = 1;
	else
		shell->is_interactive = 0;
}

void	reset(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->save_stdin != -1)
	{
		if (dup2(shell->save_stdin, STDIN_FILENO) == -1)
			return (full_exit(shell, 1));
		close(shell->save_stdin);
		shell->save_stdin = -1;
	}
	if (shell->save_stdout != -1)
	{
		if (dup2(shell->save_stdout, STDOUT_FILENO) == -1)
			return (full_exit(shell, 1));
		close(shell->save_stdout);
		shell->save_stdout = -1;
	}
	arena_clear(shell->arena);
	g_sig = 0;
	shell->cmds = NULL;
	shell->tokens = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell = NULL;
	shell = init_shell(shell, envp);
	if (shell == NULL)
		return (EXIT_FAILURE);
	set_interactive_mode(shell);
	signal_and_shlvl(shell);
	while (true)
	{
		set_fds(shell);
		read_line_input(shell, shell->line);
		if (g_sig)
		{
			g_sig = 0;
			shell->last_exit_status = 130;
			continue ;
		}
		if (parse(shell) == EXIT_SUCCESS)
			execution(shell);
		reset(shell);
	}
	full_exit(shell, shell->last_exit_status);
	return (0);
}
