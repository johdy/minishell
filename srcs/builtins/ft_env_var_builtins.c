#include "minishell.h"

void	ft_env(t_command *cmd, char **ms_environ)
{
	int i;

	i = 0;
	if (cmd->size > 1)
	{
		ft_putstr_fd("env: too many arguments\n", 1);
		return ;
	}
	while (ms_environ[i])
	{
		ft_putstr_fd(ms_environ[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void	ft_unset(t_command *cmd, char **ms_environ)
{
	int i;
	char *tmp;

	if (cmd->size == 1)
		return ;
	i = fetch_env(cmd->words[1], ms_environ);
	while (ms_environ[i])
	{
		free(ms_environ[i]);
		ms_environ[i] = ft_strdup(ms_environ[i + 1]);
		i++;
	}
}