#include "minishell.h"

char	**get_path(char **ms_environ)
{
	int i;
	char **path;
	char *first_path;

	i = 0;
	while (ms_environ[i] && ft_strncmp(ms_environ[i], "PATH=", 5))
		i++;
	if (!ms_environ[i])
		return (NULL);
	path = ft_split_path(ms_environ[i], ':');
	first_path = ft_substr(path[0], 5, ft_strlen(path[0]) - 5);
	free(path[0]);
	path[0] = first_path;
	return (path);
}

char	*get_bin(char *cmd, char **path)
{
	char *tmp;
	char *try;
	struct stat buf;
	int i;

	i = 0;
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		try = ft_strjoin(tmp, cmd);
		free(tmp);
		if (stat(try, &buf) == 0)
			return (try);
		free(try);
		i++;
	}
	return (NULL);
}