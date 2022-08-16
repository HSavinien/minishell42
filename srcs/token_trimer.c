/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_trimer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:06:22 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/16 16:07:05 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quote(char *src)
{
	int		i;
	int		j;
	int		final_size;
	char	*final;

	final_size = ft_strlen (src);
	i = 0;
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '\"')
			final_size --;
		i ++;
	}
	final = ft_calloc(final_size + 1, 1);
	i = 0;
	j = 0;
	while (src[i])
	{
		if (!(src[i] == '\'' || src[i] == '\"'))
			final[j ++] = src[i];
		i ++;
	}
	free(src);
	return (final);
}

void	remove_last_quote(char *str, char quote)
{
	int		i;

	str = ft_strrchr(str, quote);
	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i ++;
	}
}

void	remove_negative_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			ft_strlcpy(str + i, str + i + 1, ft_strlen(str + i));
		else
			i ++;
	}
}

//this take a string, and remove any quote or assimilated around the token.
char	*trim_token(char *src)
{
	char	*trimed;
	char	quote[3];

	quote[0] = src[0];
	quote[1] = -('$');
	quote[2] = '\0';
	if (*src == '\"' || *src == '\'' || *src == -('$'))
	{
		trimed = ft_strtrim(src, quote);
		remove_last_quote(trimed, quote[0]);
		free(src);
	}
	else
		trimed = remove_quote(src);
	remove_negative_char(trimed);
	return (trimed);
}
