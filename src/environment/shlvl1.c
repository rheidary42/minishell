/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 04:54:37 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 04:54:38 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		tmp;

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
		tmp = add_env_var(shell, shlvl_node, "SHLVL", shlvl);
		return (free(shlvl), tmp);
	}
	return (0);
}

void	set_interactive_mode(t_shell *shell)
{
	if (isatty(fileno(stdin)) == true)
		shell->is_interactive = 1;
	else
		shell->is_interactive = 0;
}

void	signal_and_shlvl(t_shell *shell)
{
	set_interactive_mode(shell);
	setup_signals(shell);
	rl_event_hook = rl_ev_hook;
	if (set_shlvl(shell) == 1)
		full_exit(shell, 1);
}
