#include "minishell.h"

void	ft_heredoc(char *limit)
{
	printf("calling heredoc limited by %s\n", limit);
}

int	execcmd(char **args)
{
	int i = 1;
	printf("about to execute cmd \033[1;35m%s\033[0m with args : ", args[0]);
	while (args[i])
		printf("%s ; ", args[i ++]);
	printf("\n");
	return (0);
}
