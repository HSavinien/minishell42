/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:46:28 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/02 18:56:34 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		ft_break(tmp_start, &tmp_actual);
		(void)fds;
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

t_lst_token	*aplie_chevron(t_lst_token *chevron_tok, t_lst_token **lst_start,
	t_fd_redir *fds)
{
	char		*chevron;
	char		*redirect_file;
	t_lst_token	*previous;

	if (!chevron_tok->next)
		error("redirection must be followed by a file to redirect");
	if (chevron_tok->content != (*lst_start)->content)
	{
		previous = *lst_start;
		while (previous && previous->next != chevron_tok && previous != chevron_tok)
			previous = previous->next;
		previous->next = chevron_tok->next->next;
		chevron_tok->next->next = NULL;
	}
	else
	{
		previous = (*lst_start)->next->next;
		*lst_start = previous;
	}
	chevron = chevron_tok->content;
	redirect_file = chevron_tok->next->content;
	do_redirect_chevron(chevron, redirect_file, fds);
	return (previous);
}

int	parser_chevron(t_lst_token *token, t_fd_redir *fds)
{
	t_lst_token	*re_start;
	char		**std_args;

	re_start = token;
	if (!token || !token->content)
		return (1);
	while (token)
	{
		if (is_chevron(token->content))
			token = aplie_chevron(token, &re_start, fds);
		token = token->next;
	}
	std_args = ft_construct(re_start);
	return (exec_cmd(std_args[0], std_args, g_varvalues.env));
}

int	parser_entry(t_lst_tokens *tokens, t_fd_redir *fds)
{
	t_lst_token	*save_start;
	int			nb_pipe;

	if(!tokens || tokens->content)
		return (1);
	check_forbidden_ends(token);
	nb_pipe = 0;
	save_start = tokens;
	while (tokens)
	{
		if (!ft_strcmp(tokens->content, "|"))
			nb_pipe ++;
		tokens = tokens->next;
	}
	if (!nb_pipe)
		parser_chevrons(save_start, fds);
	else
		do_pipe(save_start, nb_pipe, fds);
	return (0);
}
