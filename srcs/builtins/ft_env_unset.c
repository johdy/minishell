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
	int j;
	int	match;

	if (cmd->size == 1)
		return ;
	j = 0;
	while (j < cmd->size - 1)
	{
		match = 0;
		i = fetch_env(cmd->words[1 + j], ms_environ, 0);
		while (ms_environ[i])
		{
			match = 1;
			free(ms_environ[i]);
			if (ms_environ[i + 1])
				ms_environ[i] = ft_strdup(ms_environ[i + 1]);
			i++;
		}
		if (match)
		{
			free(ms_environ[i]);
			ms_environ[i - 1] = NULL;
		}
		j++;
	}
}
