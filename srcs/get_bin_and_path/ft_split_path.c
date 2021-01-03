#include "minishell.h"

int		ft_nbw(char *str, char c)
{
	int ret;
	int i;

	if (str == NULL || *str == '\0')
		return (0);
	i = 0;
	ret = 1;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
			ret++;
		}
		i++;
	}
	return (ret);
}

char	**ft_split_path(char *str, char c)
{
	long int	nbw;
	char		**tab;
	long int	i;

	i = 0;
	nbw = ft_nbw(str, c);
	if (!(tab = malloc(sizeof(char*) * (nbw + 1))))
		return (0);
	tab[nbw] = 0;
	if (nbw == 0)
		return (tab);
	while (i + 1 < nbw)
	{
		if (!(tab[i++] = ft_substr(str, 0, ft_strchr(str, c) - str)))
			return (NULL);
		str = ft_strchr(str, c);
		while (*str == c)
			str++;
	}
	if (nbw != 0)
		tab[nbw - 1] = ft_strdup(str);
	return (tab);
}
