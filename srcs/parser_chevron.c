/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_chevron.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:58:10 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/15 16:21:22 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//function that check we don't have consecutive pipe, consecutive chevrons...
int	check_repeting_specials(t_lst_token *token)
{
	char	*previous;

	previous = token->content;
	token = token->next;
	while (token)
	{
		if (!ft_strcmp(previous, "|") && !ft_strcmp(token->content, "|"))
			return (error("consecutive pipe forbiden", 258, token));
		if (is_chevron(previous) && is_chevron(token->content))
			return (error("consecutive chevrons forbiden", 258, token));
		if (is_chevron(previous) && !ft_strcmp(token->content, "|"))
			return (error("no file name between chevron and pipe", 258, token));
		previous = token->content;
		token = token->next;
	}
	return (0);
}

//check that the ends of the user input are not a pipe or a redirection.
int	check_forbidden_ends(t_lst_token *token)
{
	t_lst_token	*last;

	if (!ft_strcmp(token->content, "|"))
		return (error("comand cannot begin with a pipe", 258, token));
	last = token;
	while (last->next)
		last = last->next;
	if (!ft_strcmp(last->content, "|"))
		return (error("error pipe at end", 258, token));
	if (is_chevron(last->content))
		return (error("redirection cannot be done without a file dumbass."
				, 258, token));
	return (check_repeting_specials(token));
}

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
