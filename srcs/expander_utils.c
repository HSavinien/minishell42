/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:30:36 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/12 13:39:49 by tmongell         ###   ########.fr       */
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

//this function get the return value from env, and put the coresponding str 
//in dst. unlike the copy_var function, it does not put delimitor around the 
//value. it return the number of char writen on dst.
int	expand_ret_value(char *dst)
{
	char	*ret_value_str;
	int		i;

	ret_value_str = ft_itoa(g_varvalues.ret);
	i = 0;
	while (ret_value_str[i])
	{
		dst[i] = ret_value_str[i];
		i ++;
	}
	return (i);
}
