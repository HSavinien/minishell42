/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_chevron.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:58:10 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/12 17:32:18 by cmaroude         ###   ########.fr       */
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
			return (error("consecutive pipe forbiden", 258));
		if (is_chevron(previous) && is_chevron(token->content))
			return (error("consecutive chevrons forbiden", 258));
		if (is_chevron(previous) && !ft_strcmp(token->content, "|"))
			return (error("implicit file for redirection is forbiden", 258));
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
		return (error("comand cannot begin with a pipe", 258));
	last = token;
	while (last->next)
		last = last->next;
	if (!ft_strcmp(last->content, "|"))
		return (error("error pipe at end", 258));
	if (is_chevron(last->content))
		return (error("redirection cannot be done without a file dumbass.", 258));
	return (check_repeting_specials(token));
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
