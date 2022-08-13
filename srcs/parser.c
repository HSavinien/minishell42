/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:46:28 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/13 17:12:22 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_chevron(char *str)
{
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

t_lst_token	*aplie_chevron(t_lst_token *chevron_tok, t_lst_token **lst_start,
	t_fd_redir *fds, int *err)
{
	char		*chevron;
	char		*redirect_file;
	t_lst_token	*prev;

	if (!chevron_tok->next && ++(*err)
		&& error("redirection must be followed by a file to redirect", 258))
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
		return (NULL);
	return (prev);
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
			return (-1);
		if (token && !is_chevron(token->content))
			token = token->next;
	}
	std_args = ft_construct(re_start);
	return (exec_cmd(std_args[0], std_args, g_varvalues.env));
}

int	parser_entry(t_lst_token *tokens, t_fd_redir *fds)
{
	t_lst_token	*save_start;
	int			nb_pipe;

	if (!tokens || !tokens->content || check_forbidden_ends(tokens))
		return (1);
	nb_pipe = 0;
	save_start = tokens;
	while (tokens)
	{
		if (!ft_strcmp(tokens->content, "|"))
			nb_pipe ++;
		tokens = tokens->next;
	}
	if (!nb_pipe && parser_chevron(save_start, fds) < 0)
		return (1);
	else if (nb_pipe)
		do_pipe(save_start, nb_pipe, fds);
	return (0);
}
