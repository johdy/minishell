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

int		put_ret_nb(t_command *cmd, int i, int j)
{
	char *tocopy;
	char *new_word;

	tocopy = ft_itoa(cmd->prev_out);
	new_word = malloc(ft_strlen(cmd->words[i]) - 2 + ft_strlen(tocopy) + 1);
	ft_memcpy(new_word, cmd->words[i], j);
	ft_memcpy(new_word + j, tocopy, ft_strlen(tocopy));
	ft_strlcpy(new_word + j + ft_strlen(tocopy), cmd->words[i] + j + 2, ft_strlen(cmd->words[i]) - 2 + 1);
	free(cmd->words[i]);
	free(tocopy);
	cmd->words[i] = new_word;
	return (1);
}

int		replace_env(t_command *cmd, int i, int j, char **ms_environ)
{
	int sizew;
	int w;
	char *new_word;
	char *tocopy;

	j++;
	sizew = 0;
	while (!is_envvar_ending(cmd->words[i][j + sizew]) && cmd->words[i][j + sizew])
		sizew++;
	w = fetch_env(cmd->words[i] + j, ms_environ, sizew);
	j--;
	if (!ms_environ[w] && cmd->words[i][j + 1] != '?')
		return (0);
	else if (!ms_environ[w])
		return (put_ret_nb(cmd, i, j));
	new_word = malloc(ft_strlen(cmd->words[i]) - (sizew + 1) + ft_strlen(ms_environ[w]) - (sizew + 1) + 1);
	ft_memcpy(new_word, cmd->words[i], j);
	ft_memcpy(new_word + j, ms_environ[w] + sizew + 1, ft_strlen(ms_environ[w]) - (sizew + 1));
	ft_strlcpy(new_word + j + ft_strlen(ms_environ[w]) - (sizew + 1), cmd->words[i] + sizew + j + 1, ft_strlen(cmd->words[i]) - (sizew + 1) + 1);
	free(cmd->words[i]);
	cmd->words[i] = new_word;
	return (1);
}

void	lookfor_envvar(t_command *cmd, char **ms_environ)
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
				if (!replace_env(cmd, i, j, ms_environ))
					j = suppress_wrong_env(cmd, i--, j);
				j--;
			}
			j++;
		}
		i++;
	}
}
