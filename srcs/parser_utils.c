/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:14:20 by cmaroude          #+#    #+#             */
/*   Updated: 2022/07/27 14:17:36 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_structlstsize(t_lst_token *token)
{
	int	size;

	size = 0;
	while (token)
	{
		token = token->next;
		size ++;
	}
	return (size);
}

char	**ft_construct(t_lst_token *token)
{
	int		len;
	char	**std_args;
	int		i;

	len = ft_structlstsize(token);
	std_args = malloc(sizeof (char *) * (len + 1));
	if (std_args == NULL)
		return (NULL);
	i = 0;
	while (i < len && token != NULL)
	{
		std_args[i++] = ft_strdup(token->content);
		(token) = token->next;
	}
	std_args[i] = NULL;
	return (std_args);
}

void	ft_break(t_lst_token **start, t_lst_token **actual)
{
	t_lst_token	*tmp_start;

	if (actual == NULL)
		return ;
	while ((*start) != NULL)
	{
		if (ft_strcmp((*start)->content, "|") == 0)
		{
			tmp_start = *start;
			*start = NULL;
			free(tmp_start);
			break ;
		}
		start = &((*start)->next);
	}
	if (ft_strcmp((*actual)->content, "|") == 0)
	{
		*actual = (*actual)->next;
	}
}

void	ft_skip(t_lst_token **tmp, int skip)
{
	int			i;
	t_lst_token	*tmptoken;

	i = 0;
	if (*tmp == NULL)
		return ;
	tmptoken = *tmp;
	if (skip == 2)
	{
		(*tmp) = (*tmp)->next->next;
	}
	if (skip == 1)
	{		
		(*tmp) = ((*tmp)->next);
	}
}
