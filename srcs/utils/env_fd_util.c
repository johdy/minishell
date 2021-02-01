#include "minishell.h"

int		fetch_env(char *id, char **ms_environ, int size)
{
	int i;
	int match;
	int sizecomp;

	sizecomp = (size == 0 ? (int)ft_strlen(id) : size);
	match = 0;
	i = 0;
	while (!match)
	{
		if (ms_environ[i] && ft_strncmp(ms_environ[i], id, sizecomp))
			i++;
		else if (ms_environ[i])
		{
			if ((int)ft_strlen(ms_environ[i]) > sizecomp &&
				ms_environ[i][sizecomp] == '=')
				match = 1;
			else
				i++;
		}
		else
			match = 1;
	}
	return (i);
}

void	restore_std(int stdin, int stdout)
{
	if (stdin != 0)
	{
		dup2(stdin, 0);
		close(stdin);
	}
	if (stdout != 1)
	{
		dup2(stdout, 1);
		close(stdout);
	}
}
