/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:46:28 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/16 16:20:15 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	**ft_construct(t_lst_token *token)
{
	int			len;
	char		**std_args;
	int			i;
	t_lst_token	*tmp;

	len = ft_structlstsize(token);
	std_args = malloc(sizeof (char *) * (len + 1));
	if (std_args == NULL)
		return (NULL);
	i = 0;
	while (i < len && token != NULL)
	{
		tmp = token;
		if (token->content != NULL)
			std_args[i++] = trim_token(token->content);
		(token) = token->next;
		free(tmp);
	}
	std_args[i] = NULL;
	return (std_args);
}
