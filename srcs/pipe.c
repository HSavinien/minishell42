/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:34:05 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/17 18:07:41 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//function that open every pipes needed, and store them in pipe_ends. 
int	init_pipe(t_pipe_array pipe_ends, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		if (pipe(pipe_ends[i ++]))
		{
			while (i -- >= 0)
			{
				close(pipe_ends[i][1]);
				close(pipe_ends[i][0]);
			}
		}
	}
	pipe_ends[nb_pipe][0] = -1;
	pipe_ends[nb_pipe][1] = -1;
	return (0);
}

//this function take a linked list with potentialy multiple pipes
//it returns, as a linked list, the first cmd of this list (pipe not included)
//and changes the base cmd to start after this pipe
t_lst_token	*get_subcmd(t_lst_token **base_cmd, int num_cmd, int nb_pipe)
{
	t_lst_token	*sub_cmd;
	t_lst_token	*before_pipe;

	if (num_cmd == nb_pipe)
		return (*base_cmd);
	sub_cmd = *base_cmd;
	while ((*base_cmd)->next && ft_strcmp((*base_cmd)->next->content, "|"))
		(*base_cmd) = (*base_cmd)->next;
	if (!*base_cmd)
		tech_error("called pipe function on pipeless file (WTF)", 258, sub_cmd);
	before_pipe = (*base_cmd);
	*base_cmd = (*base_cmd)->next->next;
	free(before_pipe->next->content);
	free(before_pipe->next);
	before_pipe->next = NULL;
	return (sub_cmd);
}

//this function count the numbers of pipes in the pipes array.
//why count this rather than just u0sing the already existing var?
//go ask the fucking norminette
int	get_nb_pipes(t_pipe_array pipes)
{
	int	i;

	i = 0;
	while (pipes[i][0] >= 0)
		i ++;
	return (i);
}

//this function execute the action the child_process should do.
//note : the arg pip should be called pipes, but it whould make a norm error...
void	pipe_child(t_lst_token *cmd, int num, t_pipe_array pip, t_fd_redir *fd)
{
	int	nb_pipe;

	nb_pipe = get_nb_pipes(pip);
	close_unused_pipe(num, nb_pipe, pip);
	dup_pipe(num, nb_pipe, pip);
	parser_chevron(cmd, fd);
	if (num > 0)
		close(pip[num - 1][0]);
	if (num < nb_pipe)
		close(pip[num][1]);
	exit(0);
}

void	do_pipe(t_lst_token *cmd, int nb_pipe, t_fd_redir *fds)
{
	t_pipe_array	pipe_ends;
	int				*pid;
	int				num_cmd;
	t_lst_token		*sub_cmd;

	pid = ft_calloc(nb_pipe + 2, sizeof(int));
	if (!pid)
		tech_error("unexpected malloc error", 258, cmd);
	if (init_pipe(pipe_ends, nb_pipe))
		tech_error("could not open some pipes", 258, cmd);
	num_cmd = -1;
	while (++ num_cmd <= nb_pipe)
	{
		sub_cmd = get_subcmd(&cmd, num_cmd, nb_pipe);
		pid[num_cmd] = fork();
		if (pid[num_cmd] < 0)
			tech_error("that was your last forking mistake, kid", 258, cmd);
		if (!pid[num_cmd])
			return (pipe_child(sub_cmd, num_cmd, pipe_ends, fds));
		if (num_cmd)
			close_two(pipe_ends[num_cmd - 1][0], pipe_ends[num_cmd -1][1]);
		destroy_lst(sub_cmd);
	}
	wait_all_pipes(pid, num_cmd);
}
