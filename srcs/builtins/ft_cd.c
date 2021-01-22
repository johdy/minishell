#include "minishell.h"

int		print_no_such_(char *str, char *old_dir)
{
	ft_putstr_fd("cd: no such file or directory: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	free(old_dir);
	return (0);
}

int		change_directory(t_command *cmd, char *old_dirname, char **ms_environ)
{
	if (cmd->size > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 1);
		free(old_dirname);
		return (0);
	}
	if (cmd->size == 1 && ms_environ[fetch_env("HOME=", ms_environ, 4)])
	{
		if (chdir(ms_environ[fetch_env("HOME=", ms_environ, 4)] + 5))
			return (print_no_such_(ms_environ[fetch_env("HOME=", ms_environ, 4)] + 5, old_dirname));
	}
	else if (cmd->size == 1)
	{
		ft_putstr_fd("cd: HOME not set\n", 1);
		return (0);
	}
	else if (chdir(cmd->words[1]))
		return (print_no_such_(cmd->words[1], old_dirname));
	return (1);
}

void	update_env(char *new_val, char **ms_environ, char *id)
{
	int i;
	char *new_env;

	i = fetch_env(id, ms_environ, ft_strlen(id) - 1);
	if (!ms_environ[i])
		return ;
	new_env = ft_strjoin(id, new_val);
	free(ms_environ[i]);
	ms_environ[i] = new_env;
}

void	ft_cd(t_command *cmd, char **ms_environ)
{
	char *dirname;
	char *old_dirname;

	old_dirname = getcwd(NULL, 0);
	if (!change_directory(cmd, old_dirname, ms_environ))
	{
		cmd->out = 1;
		return ;
	}
	dirname = getcwd(NULL, 0);
	update_env(old_dirname, ms_environ, "OLDPWD=");
	free(old_dirname);
	update_env(dirname, ms_environ, "PWD=");
	free(dirname);
}