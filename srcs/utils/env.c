#include "minishell.h"

int		fetch_env(char *id, char **ms_environ)
{
	int i;

	i = 0;
	while (ms_environ[i] && ft_strncmp(ms_environ[i], id, ft_strlen(id)))
		i++;
	return (i);
}