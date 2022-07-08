/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:04:16 by tmongell          #+#    #+#             */
/*   Updated: 2022/04/29 19:15:36 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//free, set to NULL, and return, in a single line! What more can you wish for?
void	*ft_reset_ptr(void	*ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}
