#include "minishell.h"

void	error(char *msg)
{
	printf("Error : %s\n", msg);
	exit(42);
}
