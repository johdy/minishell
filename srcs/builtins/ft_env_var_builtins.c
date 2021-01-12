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
		i = fetch_env(cmd->words[1 + j], ms_environ);
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

void	append_env(char *str, char ***ms_environ)
{
	int i;
	char **env;
	char **new_env;

	env = *ms_environ;
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char*) * (i + 2));
	i = -1;
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	clean_path(env);
	*ms_environ = new_env;
}

int		check_exp(char *str, int i)
{
	return (1);
}

void	ft_export(t_command *cmd, char ***ms_environ)
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
		i = find_eq(cmd->words[1 + j]);
		if (check_exp(cmd->words[1 + j], i))
			append_env(cmd->words[1 + j], ms_environ);
		j++;
	}
}
