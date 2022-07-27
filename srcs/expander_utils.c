/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:30:36 by cmaroude          #+#    #+#             */
/*   Updated: 2022/07/27 17:39:43 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//find the longest var in env, and return it's len.
//maxlen start at 3 because $? is 3 digit long max.
int	max_var_len(char **env)
{
	int	i;
	int	max_len;
	int	tmp_len;

	max_len = 3;
	i = 0;
	while (env[i])
	{
		tmp_len = ft_strlen(env[i ++]);
		if (tmp_len > max_len)
			max_len = tmp_len;
	}
	return (max_len + 2);
}
