/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:11:48 by tmongell          #+#    #+#             */
/*   Updated: 2022/07/25 14:49:28 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_quote(char *line, char quote)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != quote)
		i ++;
	if (!line[i])
		error("quotes not closed");
	return (i + 1);
}

int	lexer_checkcase(char	*line)
{
	if (line[0] == '\'' || line[0] == '\"' || line[0] == -'$')
		return (handle_quote(line, line[0]));
	else
		return (1);
}

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
		return;
	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i ++;
	}
}

char	*trim_token(char *src)
{
	char	*trimed;
	char	quote[3];
	
	quote[0] = src[0];
	quote[1] = -'$';
	quote[2] = '\0';
	if (*src == '\"' || *src == '\'' || *src == -'$')
	{
		trimed = ft_strtrim(src, quote);
		remove_last_quote(trimed, quote[0]);
		free(src);
	}
	else
		trimed = remove_quote(src);
	return (trimed);
}
