/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:45:01 by jdyer             #+#    #+#             */
/*   Updated: 2020/02/04 20:45:03 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# define BUFFER_SIZE 4096

int		get_next_line(int fd, char **line, char **reste);
int		ft_strilen(char *str);
int		get_chariot(char *str);
char	*f_strcat(char **str1, char *str2, int nb);
char	*f_strcpy(char *src, int beg, int end);
#endif
