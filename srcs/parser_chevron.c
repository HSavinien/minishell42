/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_chevron.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:58:10 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/16 16:22:13 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	do_redirect_chevron_in(char *chevron, char *file, t_fd_redir *fds)
{
	close(fds->in);
	if (!ft_strcmp(chevron, "<<"))
		ft_heredoc(file, fds);
	else if (!ft_strcmp(chevron, "<"))
	{
		fds->in = open(file, O_RDONLY);
		if (fds->in < 0)
			return (open_error(file, 1));
		dup2(fds->in, 0);
	}
	else
		return (tech_error("entered redir_chevron_in with wrong chevron", 258));
	return (0);
}

int	do_redirect_chevron_out(char *chevron, char *file, t_fd_redir *fds)
{
	close(fds->out);
	if (!ft_strcmp(chevron, ">>"))
		fds->out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (!ft_strcmp(chevron, ">"))
		fds->out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds->out < 0)
		return (open_error(file, 1));
	dup2(fds->out, 1);
	return (0);
}

int	do_redirect_chevron(char *chevron, char *file, t_fd_redir *fds)
{
	if (chevron[0] == '<')
		return (do_redirect_chevron_in(chevron, file, fds));
	else if (chevron[0] == '>')
		return (do_redirect_chevron_out(chevron, file, fds));
	return (0);
}

t_lst_token	*aplie_chevron(t_lst_token *chevron_tok, t_lst_token **lst_start,
	t_fd_redir *fds, int *err)
{
	char		*chevron;
	char		*redirect_file;
	t_lst_token	*prev;

	if (!chevron_tok->next && ++(*err)
		&& error("chevron must be followed by a file name", 258, *lst_start))
		return (NULL);
	if (chevron_tok->content != (*lst_start)->content)
	{
		prev = *lst_start;
		while (prev && prev->next != chevron_tok && prev != chevron_tok)
			prev = prev->next;
		prev->next = chevron_tok->next->next;
		chevron_tok->next->next = NULL;
	}
	else
	{
		prev = (*lst_start)->next->next;
		*lst_start = prev;
	}
	chevron = chevron_tok->content;
	redirect_file = chevron_tok->next->content;
	if (do_redirect_chevron(chevron, redirect_file, fds) && ++(*err))
		return (destroy_chevron_lst(chevron_tok, NULL));
	return (destroy_chevron_lst(chevron_tok, prev));
}

int	parser_chevron(t_lst_token *token, t_fd_redir *fds)
{
	t_lst_token	*re_start;
	char		**std_args;
	int			err;

	err = 0;
	re_start = token;
	if (!token || !token->content)
		return (1);
	while (token)
	{
		if (is_chevron(token->content))
			token = aplie_chevron(token, &re_start, fds, &err);
		if (err != 0)
			return ((int) destroy_lst(re_start) - 1);
		if (token && !is_chevron(token->content))
			token = token->next;
	}
	std_args = ft_construct(re_start);
	return (exec_cmd(std_args[0], std_args, g_varvalues.env));
}
