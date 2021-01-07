#include "minishell.h"

int		change_directory(t_command *cmd, char *old_dirname)
{
	if (cmd->size > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 1);
		free(old_dirname);
		return (0);
	}
	if (cmd->size == 1 && environ[fetch_env("HOME=")])
		chdir(environ[fetch_env("HOME=")] + 5);
	else if (chdir(cmd->words[1]))
	{
		ft_putstr_fd("cd: no such file or directory: ", 1);
		ft_putstr_fd(cmd->words[1], 1);
		ft_putstr_fd("\n", 1);
		free(old_dirname);
		return (0);
	}
	return (1);
}

void	update_env(char *new_val, char *id)
{
	int i;
	char *new_env;

	i = fetch_env(id);
	if (!environ[i])
		return ;
	new_env = ft_strjoin(id, new_val);
	environ[i] = new_env;
}

void	ft_cd(t_command *cmd)
{
	char *dirname;
	char *old_dirname;

	old_dirname = getcwd(NULL, 0);
	if (!change_directory(cmd, old_dirname))
		return ;
	dirname = getcwd(NULL, 0);
	update_env(old_dirname, "OLDPWD=");
	free(old_dirname);
	update_env(dirname, "PWD=");
	free(dirname);
}