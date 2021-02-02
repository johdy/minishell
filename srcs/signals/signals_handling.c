/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:02:01 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 11:02:02 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigc(int mask)
{
	(void)mask;
	ft_putstr_fd("\b\b  \b\b\nminishell > ", 1);
}

void	sigc_fork(int mask)
{
	(void)mask;
	ft_putstr_fd("\n", 1);
}

void	sigbs(int mask)
{
	(void)mask;
	ft_putstr_fd("\b\b  \b\b", 1);
}

void	sigbs_fork(int mask)
{
	(void)mask;
	ft_putstr_fd("Quit: ", 1);
	ft_putnbr_fd(mask, 1);
	ft_putstr_fd("\n", 1);
}
