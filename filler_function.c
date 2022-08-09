#include "minishell.h"

void	error(char *msg)
{
	printf("Error : %s\n", msg);
	exit(42);
}

int	ft_cd(int argc, char **argv)
{
	printf("filler for cmd cd\n");
	(void) argv[argc];
	return 0;
}

int	ft_export(int argc, char **argv)
{
	printf("filler for cmd export\n");
	(void) argv[argc];
	return 0;
}

int	ft_echo(int argc, char **argv)
{
	printf("filler for cmd echo\n");
	(void) argv[argc];
	return 0;
}
