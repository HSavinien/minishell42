#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include "libft/libft.h"

void	do_cmd(char *fct, char** args, char **env);

void	do_pipe(char** lex, int pipose, char **env)
{
	int i = 0;
	int	pipe_fd[2];

	dprintf(2, "fool of a took!\n");	
	lex[pipose] = NULL;
	pipe(pipe_fd);
	dup2(pipe_fd[1], 1);
	do_lexer(lex, env);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	do_cmd(lex[pipose + 1], lex + pipose + 2, env);
	do_lexer(lex + pipose + 1, env);
	close(pipe_fd[0]);
}

int	do_lexer(char **lex, char **env)
{
	int		i = 0;

	while (lex[i])
	{
		if (lex[i][0] == '|')
		{
			do_pipe(lex, i, env);
			return (1);
		}
		i ++;
	}
	do_cmd(lex[0], lex + 1, env);
}

int	main(int ac, char **av, char **env)
{
	char **lex;

	if (ac != 2)
		return (printf("nope\n"));
	lex = ft_split_word(av[1]);
	do_lexer(lex, env);
}
