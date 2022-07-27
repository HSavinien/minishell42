/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:46:28 by cmaroude          #+#    #+#             */
/*   Updated: 2022/07/27 17:25:22 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_pipe(t_lst_token *first_cmd, t_lst_token *sec_cmd, t_fd_redir *fds)
{
	int	pipe_fd[2];
	int	first_pid;
	int	sec_pid;

	if (pipe(pipe_fd))
		tech_error("coud not create pipe");
	dup2(pipe_fd[1], 1);
	first_pid = fork();
	if (!first_pid)
		exit (ft_parser(first_cmd, fds));
	dup2(fds->base_stdout, 1);
	dup2(pipe_fd[0], 0);
	sec_pid = fork();
	if (!sec_pid)
	{
		exit (ft_parser(sec_cmd, fds));
	}
	waitpid(sec_pid, &sec_pid, 0);
	waitpid(first_pid, &first_pid, 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	dup2(fds->base_stdin, 0);
}

int	verif_pipe(t_lst_token *start, t_lst_token *actual, t_fd_redir *fds)
{
	t_lst_token	*tmp_start;
	t_lst_token	*tmp_actual;

	tmp_start = start;
	tmp_actual = actual;
	if (actual == NULL)
		return (0);
	if (ft_strcmp(actual->content, "|") == 0)
	{	
		ft_break(&tmp_start, &tmp_actual);
		do_pipe(tmp_start, tmp_actual, fds);
		return (1);
	}
	else
		return (0);
}

int	is_chevron(char *str)
{
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

t_lst_token	*aplie_chevron(t_lst_token *chevron_tok, t_lst_token *lst_start,
	t_fd_redir *fds)
{
	char		*chevron;
	char		*redirect_file;
	t_lst_token	*previous;

	if (!chevron_tok->next)
		error("redirection must be followed by a file to redirect");
	previous = lst_start;
	chevron = chevron_tok->content;
	redirect_file = chevron_tok->next->content;
	while (previous->next != chevron_tok)
		previous = previous->next;
	previous->next = chevron_tok->next->next;
	chevron_tok->next->next = NULL;
	do_redirect_chevron(chevron, redirect_file, fds);
	destroy_lst(chevron_tok);
	return (previous);
}

int	ft_parser(t_lst_token *token, t_fd_redir *fds)
{
	t_lst_token	*re_start;
	char		**std_args;

	re_start = token;
	if (!token || !token->content)
		return (1);
	check_forbidden_ends(token);
	while (token)
	{
		if (verif_pipe(re_start, token, fds) == 1)
			return (1);
		else if (token != NULL)
			token = token->next;
	}
	token = re_start;
	while (token)
	{
		if (is_chevron(token->content))
			token = aplie_chevron(token, re_start, fds);
	token = token->next;
	}
	std_args = ft_construct(re_start);
	return (execcmd(std_args));
}
