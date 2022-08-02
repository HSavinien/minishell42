# include "../minishell.h"

void	close_all_except(int *pipes[2], int except1, int except2)
{
	if (!pipes)
		return ;
	while (pipes)
	{
		if (pipes[0] != except1 && pipes[0] != except2)
			close(pipes[0]);
		if (pipes[1] != except1 && pipes[1] != except2)
			close(pipes[1]);
		pipes++;
	}
}
