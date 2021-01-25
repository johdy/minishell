#include "minishell.h"

void	sigc(int mask)
{
	ft_putstr_fd("\b\b  \b\b\nminishell > ", 1);
}

void	sigc_fork(int mask)
{
	ft_putstr_fd("\n", 1);
}

void	sigbs(int mask)
{
	ft_putstr_fd("\b\b  \b\b", 1);
}

void	sigbs_fork(int mask)
{
	ft_putstr_fd("Quit: ", 1);
	ft_putnbr_fd(mask, 1);
	ft_putstr_fd("\n", 1);
}
