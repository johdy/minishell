/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:44:41 by jdyer             #+#    #+#             */
/*   Updated: 2020/02/04 20:44:42 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	flush_reste(char **reste, char **line)
{
	char	*tmp;
	int		recreate;

	recreate = (get_chariot(*reste) < ft_strilen(*reste) - 1) ? 1 : 0;
	if (ft_strilen(*reste) == 0)
		return (-2);
	tmp = NULL;
	free(*line);
	*line = f_strcpy(*reste, 0, get_chariot(*reste));
	if (recreate == 1)
	{
		tmp = f_strcpy(*reste, get_chariot(*reste) + 1, ft_strilen(*reste));
		free(*reste);
		*reste = f_strcpy(tmp, 0, ft_strilen(tmp));
	}
	if (recreate == 0 && ft_strilen(*reste) > 0)
	{
		free(*reste);
		*reste = NULL;
	}
	free(tmp);
	tmp = NULL;
	return (1);
}

int	append_reste(char **reste, char *buf)
{
	if (ft_strilen(*reste) == 0)
		*reste = f_strcpy(buf, 0, ft_strilen(buf));
	else
		*reste = f_strcat(reste, buf, get_chariot(buf));
	return (2);
}

int	fill_line(char **reste, char *buf, char **line, int debug)
{
	flush_reste(reste, line);
	*line = f_strcat(line, buf, get_chariot(buf));
	if (debug > 0 && get_chariot(buf) != BUFFER_SIZE - 1)
	{
		free(*reste);
		*reste = f_strcpy(buf, get_chariot(buf) + 1, ft_strilen(buf));
	}
	return (1);
}

int	read_the_file(int fd, char **line, char **reste)
{
	int		debug;
	char	buf[BUFFER_SIZE + 1];

	debug = read(fd, buf, BUFFER_SIZE);
	if (debug == -1)
	{
		free(*line);
		*line = NULL;
		return (debug);
	}
	buf[debug] = '\0';
	if (debug > 0 && get_chariot(buf) < debug)
		return (fill_line(reste, buf, line, debug));
	if (debug == BUFFER_SIZE)
		return (append_reste(reste, buf));
	else
		fill_line(reste, buf, line, debug);
	return (0);
}

int	get_next_line(int fd, char **line, char **reste)
{
	int			check;

	check = 2;
	if (BUFFER_SIZE < 1 || BUFFER_SIZE > 8192000000 || line == NULL)
		return (-1);
	*line = malloc(sizeof(char));
	**line = '\0';
	if (ft_strilen(*reste) > 0 && get_chariot(*reste) != ft_strilen(*reste))
		return (flush_reste(reste, line));
	while (check == 2)
		check = read_the_file(fd, line, reste);
	return (check);
}
