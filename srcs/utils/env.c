#include "minishell.h"

int		fetch_env(char *id)
{
	int i;

	i = 0;
	while (environ[i] && ft_strncmp(environ[i], id, ft_strlen(id)))
		i++;
	return (i);
}