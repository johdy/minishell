#include "minishell.h"

int main(void)
{
	char *line;
	int deb;
	int opfile;
	int out;
	char *bn;

	bn = ft_strdup("\n");
	opfile = open("minimalraw.log", O_RDONLY, 777);
	out = open("out", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while ((deb = get_next_line(opfile, &line)) > 0)
	{
		printf("%s\n", line);
		if (ft_strncmp(line, "==55648==", 6))
		{
			ft_putstr_fd(line, out);
			ft_putstr_fd(bn, out);
		}
	}
	return (1);
}

