/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:18:19 by cmaroude          #+#    #+#             */
/*   Updated: 2022/07/20 14:19:03 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_heredoc(t_lst_token *token, t_lst_token *tmp)
{
	printf("TOKEN:%s\n", (token)->content);
	printf("LIMIT:%s\n", (tmp)->content);
	printf("Let's handle heredoc\n");
}
