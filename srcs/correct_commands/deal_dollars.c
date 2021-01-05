#include "minishell.h"

int		delete_word(t_command *cmd, int i)
{
	int cpt;

	cpt = 0;
	while (cmd->words[i + cpt + 1])
	{
		free(cmd->words[i + cpt]);
		cmd->words[i + cpt] = ft_strdup(cmd->words[i + cpt + 1]);
		cmd->stickits[i + cpt] = cmd->stickits[i + cpt + 1];
		cmd->quotes[i + cpt] = cmd->quotes[i + cpt + 1];
		cpt++;
	}
	free(cmd->words[i + cpt]);
	free(cmd->words[i + cpt + 1]);
	cmd->words[i + cpt] = NULL;
	cmd->stickits[i + cpt] = -1;
	cmd->quotes[i + cpt] = -1;
	cmd->size--;
	return (-1);
}

int		suppress_wrong_env(t_command *cmd, int i, int j)
{
	char *new_word;
	int cpt;

	cpt = 0;
	if (j == 0)
		return (delete_word(cmd, i));
	new_word = ft_substr(cmd->words[i], 0, j);
	free(cmd->words[i]);
	cmd->words[i] = new_word;
	return (-1);
}

int		is_envvar_ending(char c)
{
	if (ft_isalnum(c))
		return (0);
	if (c == '_')
		return (0);
	return (1);
}

int		replace_env(t_command *cmd, int i, int j)
{
	int sizew;
	int w;
	char *new_word;

	j++;
	sizew = 0;
	while (!is_envvar_ending(cmd->words[i][j + sizew]) && cmd->words[i][j + sizew])
		sizew++;
	w = 0;
	while (environ[w] && ft_strncmp(environ[w], cmd->words[i] + j, sizew))
		w++;
	j--;
	if (!environ[w])
		return (0);
	new_word = malloc(ft_strlen(cmd->words[i]) - (sizew + 1) + ft_strlen(environ[w]) - (sizew + 1) + 1);
	ft_memcpy(new_word, cmd->words[i], j);
	ft_memcpy(new_word + j, environ[w] + sizew + 1, ft_strlen(environ[w]) - (sizew + 1));
	ft_strlcpy(new_word + j + ft_strlen(environ[w]) - (sizew + 1), cmd->words[i] + sizew + j + 1, ft_strlen(cmd->words[i]) - (sizew + 1) + 1);
	free(cmd->words[i]);
	cmd->words[i] = new_word;
	return (1);
}

void	lookfor_envvar(t_command *cmd)
{
	int i;
	int j;

	i = 0;
	while (cmd->words[i])
	{
		j = 0;
		while (j >= 0 && cmd->words[i][j])
		{
			if (cmd->words[i][j] == '$' && !cmd->quotes[i])
			{
				if (!replace_env(cmd, i, j))
					j = suppress_wrong_env(cmd, i--, j);
				j--;
			}
			j++;
		}
		i++;
	}
}