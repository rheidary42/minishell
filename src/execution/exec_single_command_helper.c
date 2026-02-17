/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command_helper.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:02:04 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 03:02:05 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_exit_status(t_shell *shell)
{
	shell->last_exit_status = 1;
	return (1);
}

char	**set_envp(t_shell *shell, t_cmd *cmd, t_exec *exec, int *builtin_id)
{
	char	**envp;

	envp = convert_envp(shell);
	if (envp == NULL)
	{
		shell->last_exit_status = 1;
		free_and_close(shell, cmd, exec);
	}
	*builtin_id = is_builtin(cmd->argv[0]);
	return (envp);
}

void	no_final_path(t_shell *shell, t_cmd *cmd, t_exec *exec, char **envp)
{
	char	*cwd;
	char	*temp;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		temp = str_join3(cwd, "/", cmd->argv[0], shell);
		if (access(temp, X_OK) == 0)
		{
			close_shell_fds(shell);
			execve(temp, cmd->argv, envp);
			exec->errno_save = errno;
			free(cwd);
			read_errno(shell, cmd, exec);
		}
		free(cwd);
	}
	write(STDERR_FILENO, cmd->argv[0], ft_strlen(cmd->argv[0]));
	write(STDERR_FILENO, ": command not found\n", 21);
	shell->last_exit_status = 127;
	free_and_close(shell, cmd, exec);
}

void	read_errno(t_shell *shell, t_cmd *cmd, t_exec *exec)
{
	perror(cmd->argv[0]);
	if (exec->errno_save == EACCES)
		shell->last_exit_status = 126;
	else
		shell->last_exit_status = 127;
	free_and_close(shell, cmd, exec);
}

void	detect_signals(t_shell *shell, int status)
{
	int	sig_num;

	sig_num = WTERMSIG(status);
	if (sig_num == SIGINT)
	{
		write(1, "\n", 1);
	}
	if (sig_num == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 20);
	}
	shell->last_exit_status = 128 + sig_num;
}
