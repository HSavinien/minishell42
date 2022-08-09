/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_chevron.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:58:10 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/08 17:13:36 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//function that check we don't have consecutive pipe, consecutive chevrons...
void	check_repeting_specials(t_lst_token *token)
{
	char	*previous;

	previous = token->content;
	token = token->next;
	while (token)
	{
		if (!ft_strcmp(previous, "|") && !ft_strcmp(token->content, "|"))
			error("consecutive pipe forbiden");
		if (is_chevron(previous) && is_chevron(token->content))
			error("consecutive chevrons forbiden");
		if (is_chevron(previous) && !ft_strcmp(token->content, "|"))
			error("implicit file for redirection is forbiden");
		previous = token->content;
		token = token->next;
	}
}

//check that the ends of the user input are not a pipe or a redirection.
void	check_forbidden_ends(t_lst_token *token)
{
	t_lst_token	*last;

	if (!ft_strcmp(token->content, "|"))
		error("comand cannot begin with a pipe");
	last = token;
	while (last->next)
		last = last->next;
	if (!ft_strcmp(last->content, "|"))
		error("error pipe at end");
	if (is_chevron(last->content))
		error("redirection cannot be done without a file dumbass.");
	check_repeting_specials(token);
}

void	do_redirect_chevron_in(char *chevron, char *file, t_fd_redir *fds)
{
	close(fds->in);
	if (!ft_strcmp(chevron, "<<"))
		ft_heredoc(file, fds);
	else if (!ft_strcmp(chevron, "<"))
	{
		fds->in = open(file, O_RDONLY);
		if (fds->in < 0)
			open_error(file);
		dup2(fds->in, 0);
	}
	else
		tech_error("entered redir_chevron_in with wrong chevron");
}

void	do_redirect_chevron_out(char *chevron, char *file, t_fd_redir *fds)
{
	close(fds->out);
	if (!ft_strcmp(chevron, ">>"))
		fds->out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (!ft_strcmp(chevron, ">"))
		fds->out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds->out < 0)
		open_error(file);
	dup2(fds->out, 1);
}

void	do_redirect_chevron(char *chevron, char *file, t_fd_redir *fds)
{
	if (chevron[0] == '<')
		do_redirect_chevron_in(chevron, file, fds);
	else if (chevron[0] == '>')
		do_redirect_chevron_out(chevron, file, fds);
}
