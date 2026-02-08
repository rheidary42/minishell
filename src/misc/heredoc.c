/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:38:46 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 03:38:47 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_expander(t_shell *shell, char *line)
{
	char	*exp_line;
	int		len;
	int		exp_i;
	int		i;

	len = full_line_len(shell, line);
	exp_line = arena_push(shell->arena, (sizeof(char) * len) + 1, 0, shell);
	exp_i = 0;
	i = 0;
	while (line != NULL && line[i] != '\0')
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			copy_exit_code(shell, &exp_line[exp_i], &exp_i);
			i++;
		}
		else if (line[i] == '$')
		{
			i += expand_var(shell, &exp_line[exp_i], &line[i + 1], &exp_i) + 1;
		}
		if (line[i] != '$' && line[i] != '\0')
			exp_line[exp_i++] = line[i++];
	}
	return (exp_line);
}

int	run_heredoc(t_shell *shell, char *tmp_file, char *delim, bool was_q)
{
	char	*line;
	int		fd;

	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		if (shell->is_interactive == true)
			line = readline("> ");
		else
			line = gnl_mode();
		if (handle_sigint(line, fd) == 130)
			return (130);
		if (handle_eof(line, delim) == 1)
			break ;
		if (was_q == false)
			handle_exp(shell, line, fd);
		else
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (close(fd), 0);
}

int	init_heredoc(t_shell *shell, t_redir *r)
{
	char	*tmp;

	tmp = get_here_doc_name(shell);
	if (run_heredoc(shell, tmp, r->file, r->was_quoted) == 130)
	{
		unlink(tmp);
		setup_signals(shell);
		return (1);
	}
	r->file = tmp;
	return (0);
}

int	heredoc_collector(t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*r;

	setup_signals(shell);
	cmd = shell->cmds;
	while (cmd != NULL)
	{
		r = cmd->redir;
		while (r != NULL)
		{
			if (r->type == TOKEN_HEREDOC)
			{
				if (init_heredoc(shell, r) == 1)
					return (1);
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
	setup_signals(shell);
	return (0);
}
