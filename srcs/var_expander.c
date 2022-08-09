/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:26:56 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/09 18:46:06 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//get a wide estimate of the size of the expanded linei. 
//it will always alocate wider than necessary, cause we don't want no segfault
char	*alocate_line(char *src)
{
	int	i;
	int	nb_var;

	i = 0;
	nb_var = 0;
	while (src[i])
	{
		if (src[i ++] == '$')
			nb_var ++;
	}
	nb_var *= max_var_len(g_varvalues.env);
	return (ft_calloc(i + 1 + nb_var, sizeof(char)));
}

//the main function malloc more memory than needed, this function get ride of
//any unnecessary alocated byte
char	*opti_line(char *src)
{
	char	*opti;

	opti = ft_strdup(src);
	free (src);
	return (opti);
}

//read a string from the '$' symbole in pos i up to next space/special char,
//and return the resulting substr. also incremente i to bring it to said 
//stoping char.
char	*get_var_name(char *src, int *i)
{
	int	len;
	int	start;

	start = *i;
	start ++;
	len = 0;
	while (src[*i] && !ft_isspace(src[*i]) && src[*i] != '\"')
	{
		len ++;
		*i = *i + 1;
	}
	return (ft_substr(src, start, len - 1));
}

//search a var of given name in env, and write it's value in dst.
//for lexer purpose, the value is writen between double quote.
int	copy_var(char *var_name, char *dst)
{
	int		i;
	int		j;
	int		namelen;
	char	*tmp_str;

	tmp_str = ft_strjoin(var_name, "=");
	namelen = ft_strlen(tmp_str);
	i = 0;
	while (g_varvalues.env[i]
		&& strncmp(g_varvalues.env[i], tmp_str, namelen))
		i ++;
	free (tmp_str);
	if (!g_varvalues.env[i])
		return (0);
	tmp_str = ft_strchr(g_varvalues.env[i], '=') + 1;
	j = 0;
	i = 0;
	dst[j ++] = -('$');
	while (tmp_str[i])
		dst[j ++] = tmp_str[i ++];
	dst[j ++] = -('$');
	return (j);
}

//first step of parsing : take a str, replace var name by their value, and 
//return the result. since the line to read is freed, it should have been 
//alocated with malloc beforehand.
char	*expand_vars(char *src)
{
	int		quote_on;
	char	*final_line;
	char	*var_name;
	int		i;
	int		j;

	quote_on = 0;
	i = 0;
	j = 0;
	final_line = alocate_line(src);
	while (src[i])
	{
		if (src[i] == '\'')
			quote_on = quote_on + 1 % 2;
		if (src[i] == '$' && !quote_on && src[i - 1] != '\\')
		{
			var_name = get_var_name(src, &i);
			j += copy_var(var_name, final_line + j);
			free(var_name);
		}
		else
			final_line[j ++] = src[i ++];
	}
	free (src);
	return (opti_line(final_line));
}
