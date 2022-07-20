/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:46:28 by cmaroude          #+#    #+#             */
/*   Updated: 2022/07/20 14:34:06 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_do_pipe(t_lst_token **avpipe, t_lst_token **appipe)
{
	int		i;
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

void	ft_redirect(t_lst_token **token)
{
	t_lst_token	*tmp;

	tmp = *token;
	if (ft_strcmp((*token)->content, ">>") == 0)
	{
		//redirect outfile append;
	}
	if (ft_strcmp((*token)->content, ">") == 0)
	{
		//redirect outfile normal;
	}
	if (ft_strcmp((*token)->content, "<") == 0)
	{
		//redirect infile;
	}
	printf("TOKEN:%s\n", (*token)->content);
	tmp = ((tmp)->next);
	printf("REDIRECT FILE:%s\n", (tmp)->content);
	printf("Let's handle redirect\n");
}

int	verif_redirect(t_lst_token **start, t_lst_token **actual)
{
	t_lst_token	*tmp_act;

	tmp_act = *actual;
	if (actual == NULL)
		return (0);
	if (strcmp((*actual)->content, ">") == 0 || \
			ft_strcmp((*actual)->content, "<") == 0 || \
			ft_strcmp((*actual)->content, ">>") == 0)
	{
		ft_redirect(&tmp_act);
		//prend pipe et redirect et les mets dans une var tmp qui pointe NULL
		ft_skip(actual, 2);
		ft_parser(actual);
		return (1);
	}
	if (strcmp((*actual)->content, "<<") == 0)
	{
		ft_heredoc(*actual, tmp_act);
		ft_skip(actual, 2);
		ft_parser(actual);
		return (1);
	}
	else
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
	t_lst_token	*start;
	char		**std_args;

	start = *token;
	if (*token == NULL)
		return ;
	while ((*token) != NULL)
	{
		if (verif_pipe(&start, token) == 1)
			return ;
		else if (verif_redirect(&start, token) == 1)
		{
			token = &start;
		}
		else if ((*token) != NULL)
			(token) = &((*token)->next);
	}
	std_args = ft_construct(&start);
	if (std_args == NULL)
	{
		printf("Error\n");
		return ;
	}
//	execcmd(cmd, args, env)
}
