/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:06:24 by tmongell          #+#    #+#             */
/*   Updated: 2022/04/29 19:14:01 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list	next;

	next = *(lst)->next;
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
	*lst = next;
}
