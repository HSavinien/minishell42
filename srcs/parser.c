/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:46:28 by cmaroude          #+#    #+#             */
/*   Updated: 2022/07/22 15:18:00 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_do_pipe(t_lst_token **avpipe, t_lst_token **appipe)
{
	char	**av_pipe;
	char	**ap_pipe;

	av_pipe = ft_construct(avpipe);
	ap_pipe = ft_construct(appipe);
	if ((*avpipe) == NULL)
	{	
		printf("error");
		return ;
	}
	ft_parser(avpipe);
	if ((*appipe) == NULL)
	{
		printf("error\n");
		return ;
	}
	ft_parser(appipe);
}

int	ft_redirect(t_lst_token *token, int redir)
{
	t_lst_token	*tmp;

	tmp = token;
	tmp = ((tmp)->next);
	if (redir == 0)
		return (0);
	if (tmp->next == NULL)
	{
		printf("ERROR\n");
		return (-1);
	}
	if (redir == 1)
		;/*redirect > || <*/
	if (redir == 2)
		;/*redirect >>*/
	if (redir == 3)
		ft_heredoc(token, tmp);
	printf("Let's handle redirect\n");
	return (1);
}

int	verif_redirect(t_lst_token **actual)
{
	t_lst_token	*tmp_act;
	int			redir;
	int			verif;

	tmp_act = *actual;
	redir = 0;
	if (*actual == NULL)
		return (0);
	if (strcmp((*actual)->content, ">") == 0 \
			|| ft_strcmp((*actual)->content, "<") == 0)
		redir = 1;
	if (ft_strcmp((*actual)->content, ">>") == 0)
		redir = 2;
	if (ft_strcmp((*actual)->content, "<<") == 0)
		redir = 3;
	verif = ft_redirect(tmp_act, redir);
	if (verif == -1)
		return (-1);
	if (verif == 1)
	{	
		ft_skip(actual, 2);
		ft_parser(actual);
	}
	return (0);
}

int	verif_pipe(t_lst_token **start, t_lst_token **actual)
{
	t_lst_token	*tmp_start;
	t_lst_token	*tmp_actual;

	tmp_start = *start;
	tmp_actual = *actual;
	if (actual == NULL)
		return (0);
	if (ft_strcmp((*actual)->content, "|") == 0)
	{	
		ft_conc(&tmp_start, &tmp_actual);
		ft_do_pipe(&tmp_start, &tmp_actual);
		return (1);
	}
	else
		return (0);
}

void	ft_parser(t_lst_token **token)
{
	t_lst_token	**re_start;
	t_lst_token	*tmpstart;
	char		**std_args;
	int			i;

	re_start = token;
	tmpstart = *re_start;
	if (*token == NULL)
		return ;
	while ((*token) != NULL)
	{
		if (verif_pipe(&tmpstart, token) == 1)
			return ;
		else if ((*token) != NULL)
			token = &((*token)->next);
	}
	while (*re_start != NULL)
	{
		if (verif_redirect(re_start) == -1)
			return ;
		else if (*re_start != NULL)
			re_start = &((*re_start)->next);
	}
	std_args = ft_construct(&tmpstart);
// execmd();
}
