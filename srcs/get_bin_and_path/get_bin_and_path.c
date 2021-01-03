#include "minishell.h"

char	**get_path(void)
{
	int i;
	char **path;
	char *first_path;

	i = 0;
	while (environ[i] && ft_strncmp(environ[i], "PATH=", 5))
		i++;
	path = ft_split_path(environ[i], ':');
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
	if (stat(cmd, &buf) == 0)
		return (ft_strdup(cmd));
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		try = ft_strjoin(tmp, cmd);
		free(tmp);
		if (stat(try, &buf) == 0)
			return (try);
		free(try);
		i++;
	}
	return (ft_strdup(cmd));
}