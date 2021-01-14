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


int		check_export(char *str, int i)
{
	if (i == 0)
		return (-1);
	if (i == ft_strlen(str) - 1)
		return (1);
	if ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' &&str[0] <= 'Z')  || str[0] == '_')
		return (1);
	return (-1);
}

int		deal_wrong_export(char *str, int i, int j)
{
	int err_nb;

	err_nb = check_export(str, i);
	if (err_nb == -1)
	{
		ft_putstr_fd("export: not valid in this context: ", 1);
		write(1, str, i);
		write(1, "\n", 1);
	}
	return (j + 1);
}

void	ft_export(t_command *cmd, char ***ms_environ)
{
	int i;
	int j;
	int ms_env_pos;
	char **ms_env_copy;
	
	if (cmd->size == 1)
		return ;
	j = 0;
	while (j < cmd->size - 1)
	{
		ms_env_copy = *ms_environ;
		i = find_eq(cmd->words[1 + j]);
		ms_env_pos = fetch_env(cmd->words[1 + j], ms_env_copy, i);
		if (check_export(cmd->words[1 + j], i) != 1)
			j = deal_wrong_export(cmd->words[1 + j], i, j);
		else if (ms_env_copy[ms_env_pos])
		{
			free(ms_env_copy[ms_env_pos]);
			ms_env_copy[ms_env_pos] = ft_strdup(cmd->words[1 + j++]);
		}
		else
			append_env(cmd->words[1 + j++], ms_environ);
	}
}
