/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:48:58 by tmongell          #+#    #+#             */
/*   Updated: 2022/07/28 14:51:02 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_lst(t_lst_token	*lst)
{
	while (lst)
	{
		printf("%s <> ", lst->content);
		lst = lst->next;
	}
	printf("\n");
}

void	destroy_lst(t_lst_token *lst)
{
	t_lst_token	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}
