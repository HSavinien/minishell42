/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 15:24:39 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/04 15:52:31 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	close_all_except(t_pipe_array pipes, int except1, int except2)
{
	int i;
	if (!pipes)
		return ;
	if (except1 <= 2)
		except1 = -1;
	if (except2 <= 2)
		except2 = -1;
	i = 0;
	while (pipes[i][0] >= 0)
	{
		if (pipes[i][0] != except1 && pipes[i][0] != except2)
			close(pipes[i][0]);
		if (pipes[i][1] != except1 && pipes[i][1] != except2)
			close(pipes[i][1]);
		pipes++;
	}
}

void	close_unused_pipe(int num_cmd, int nb_pipe, t_pipe_array pipes)
{
	if (num_cmd == 0)
		close_all_except(pipes, -1, pipes[num_cmd][1]);
	else if (num_cmd == nb_pipe)
		close_all_except(pipes, pipes[num_cmd -1][0], -1);
	else
		close_all_except(pipes, pipes[num_cmd -1][0], pipes[num_cmd][1]);
}

void	dup_pipe(int num_cmd, int nb_pipe, t_pipe_array pipes)
{
	if (num_cmd == 0)
		dup2(pipes[num_cmd][1], 1);
	else if (num_cmd == nb_pipe)
		dup2(pipes[num_cmd -1][0], 0);
	else
	{
		dup2(pipes[num_cmd -1][0], 0);
		dup2(pipes[num_cmd][1], 1);
	}
}
