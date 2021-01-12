#include "minishell.h"

int		fetch_env(char *id, char **ms_environ)
{
	int i;

	i = 0;
	while (ms_environ[i] && ft_strncmp(ms_environ[i], id, ft_strlen(id)))
		i++;
	return (i);
}

void	restore_std(int stdin, int stdout)
{
	dup2(stdin, 0);
	dup2(stdout, 1);
	close(stdin);
	close(stdout);
}
