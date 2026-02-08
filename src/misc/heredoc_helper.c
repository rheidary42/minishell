/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:39:00 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 03:39:01 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_eof(char *line, char *delim)
{
	if (line == NULL || ft_strcmp(line, delim) == 0)
	{
		if (line == NULL)
		{
			write(STDERR_FILENO, "warning: here-document delimited\
				by end-of-file (wanted `", 58);
			write(STDERR_FILENO, delim, ft_strlen(delim));
			write(STDERR_FILENO, "')\n", 3);
		}
		free(line);
		return (1);
	}
	return (0);
}

int	handle_sigint(char *line, int fd)
{
	if (g_sig == SIGINT)
	{
		free(line);
		close(fd);
		return (130);
	}
	return (0);
}

char	*gnl_mode(void)
{
	char	*line;
	char	*tmp;

	tmp = get_next_line(fileno(stdin));
	line = ft_strtrim(tmp, "\n");
	free(tmp);
	return (line);
}

void	handle_exp(t_shell *shell, char *line, int fd)
{
	char	*tmp;

	tmp = heredoc_expander(shell, line);
	write(fd, tmp, ft_strlen(tmp));
}

char	*get_here_doc_name(t_shell *shell)
{
	static int	heredoc_idx;
	char		*idx_str;
	char		*tmp_name;

	idx_str = ft_itoa(heredoc_idx++);
	if (idx_str == NULL)
		return (clean_up(shell), NULL);
	tmp_name = str_join3("/tmp/heredoc_", "\0", idx_str, shell);
	free(idx_str);
	return (tmp_name);
}
