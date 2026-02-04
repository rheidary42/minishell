#include "minishell.h"

int	update_pwd(t_env *env, char *oldpwd, char *pwd)
{
	t_env	*curr;

	curr = env;
	while (curr != NULL)
	{
		if (strcmp(curr->name, "PWD") == 0 && pwd)
		{
			printf("hi");
			free(curr->value);
			curr->value = ft_calloc(1, ft_strlen(pwd) + 1);
			if (!curr->value)
				return (1);
			ft_strcpy(curr->value, pwd);
		}
		if (strcmp(curr->name, "OLDPWD") == 0 && oldpwd)
		{
			free(curr->value);
			curr->value = ft_calloc(1, ft_strlen(oldpwd) + 1);
			if (!curr->value)
				return (1);
			ft_strcpy(curr->value, oldpwd);
		}
		curr = curr->next;
	}
	return (free(oldpwd), free(pwd), 0);
}

int	solo_cd(t_env *env)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	path = getenv("HOME");
	if (!path)
	{
		write(STDERR_FILENO, "cd: HOME not set\n", 18);
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		perror(NULL);
		free(oldpwd);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	return (update_pwd(env, oldpwd, pwd));
}

int	ft_cd(t_env *env, t_cmd *cmd)
{
	int		i;
	char	*oldpwd;
	char	*pwd;

	i = 0;
	while (cmd && cmd->argv[i])
		i++;
	if (i > 2)
		return (write(STDERR_FILENO, "cd: too many arguments\n", 24), 1);
	if (i == 1)
		return (solo_cd(env));
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	if (chdir(cmd->argv[1]) == -1)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(oldpwd), 1);
	return (update_pwd(env, oldpwd, pwd));
}
