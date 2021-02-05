/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fd_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:02:27 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 11:02:28 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		check_env_var(char *str, int i)
{
	int cpt;
	int eq;

	eq = 0;
	cpt = 1;
	if (i == 0)
		return (-1);
	if (!(str[0] >= 'a' && str[0] <= 'z')
		&& !(str[0] >= 'A' && str[0] <= 'Z') && !(str[0] == '_'))
		return (-1);
	while (str[cpt])
	{
		if (!eq && !(str[cpt] >= 'a' && str[cpt] <= 'z') && !(str[cpt] == '=')
			&& !(str[cpt] >= 'A' && str[cpt] <= 'Z') && !(str[cpt] == '_'))
			return (-1);
		if (str[cpt] == '=')
			eq = 1;
		cpt++;
	}
	if (i == (int)ft_strlen(str))
		return (0);
	if (i == (int)ft_strlen(str) - 1)
		return (1);
	return (1);
}

int		deal_wrong_env_var(char *str, int i, int j, t_command *cmd)
{
	int err_nb;

	err_nb = check_env_var(str, i);
	if (err_nb == -1)
	{
		ft_putstr_fd("export: `", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
		cmd->out = 1;
	}
	return (j + 1);
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
