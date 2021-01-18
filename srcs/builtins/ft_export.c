#include "minishell.h"

int		*get_ordering(char **ms_environ, int size)
{
	int *ret;
	int i;
	int cache;

	ret = malloc(sizeof(int) * (size + 1));
	i = -1;
	while (++i < size)
		ret[i] = i;
	ret[i] = -1;
	i = 0;
	while (i < size - 1)
	{
		if (ms_environ[ret[i]][0] > ms_environ[ret[i + 1]][0])
		{
			cache = ret[i + 1];
			ret[i + 1] = ret[i];
			ret[i] = cache;
			i = 0;
		}
		else
			i++;
	}
	return (ret);
}

void	display_export(char **ms_environ)
{
	int i;
	int j;
	int *class;
	int c;

	i = 0;
	while (ms_environ[i])
		i++;
	class = get_ordering(ms_environ, i);
	j = 0;
	while (j < i)
	{
		c = 0;
		ft_putstr_fd("declare -x ", 1);
		while (ms_environ[class[j]][c] != '=')
			write(1, ms_environ[class[j]] + c++, 1);
		ft_putstr_fd("=\"", 1);
		c++;
		while (ms_environ[class[j]][c])
			write(1, ms_environ[class[j]] + c++, 1);
		ft_putstr_fd("\"\n", 1);
		j++;
	}
	free(class);
}

void	ft_export(t_command *cmd, char ***ms_environ)
{
	int i;
	int j;
	int ms_env_pos;
	char **ms_env_copy;
	
	if (cmd->size == 1)
	{
		display_export(*ms_environ);
		return ;
	}
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
