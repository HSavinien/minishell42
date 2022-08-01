#include <stdio.h>

int	main(int ac, char **av)
{
	int i = 0;
	while (i < ac)
		printf("%s <> ", av[i ++]);
	printf("\n");
}
