#include "minishell.h"

void	ft_exit(t_command *cmd, char **ms_environ)
{
	clean_commands(&cmd);
	clean_path(ms_environ);
	exit(0);
}

void	ft_pwd(t_command *cmd)
{
	char *cwd;

	if (cmd->size > 1)
	{
		ft_putstr_fd("pwd: too many arguments\n", 1);
		return ;
	}
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free(cwd);
}

void	ft_echo(t_command *cmd)
{
	int i;

	i = 1;
	if (!ft_strcmp(cmd->words[i], "-n"))
		i++;
	while (cmd->words[i])
	{
		ft_putstr_fd(cmd->words[i], 1);
		if (cmd->words[++i])
			ft_putstr_fd(" ", 1);
	}
	if (ft_strcmp(cmd->words[1], "-n"))
		ft_putstr_fd("\n", 1);
}