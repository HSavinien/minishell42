/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:48:58 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/15 14:26:08 by tmongell         ###   ########.fr       */
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
		lst->next = NULL;
		free(lst->content);
		lst->content = NULL;
		free(lst);
		lst = tmp;
	}
}

//function that free a null terminated array of str, and return 0;
int	destroy_array(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (0);
}
