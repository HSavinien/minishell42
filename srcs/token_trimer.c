/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_trimer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:06:22 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/19 16:07:21 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//function that remove the char at position index in string str.
/* example :
 * char *str = "hello world";
 * remove_char(str, 4);
 * printf(%s\n, str); 
 * shall print : hell world
*/
void	remove_char(char *str, int index)
{
	ft_strlcpy(str + index, str + index + 1, ft_strlen(str + index));
}

//return the index of the char before the quote
int	remove_quote(char *src, char quote, int pos)
{
	remove_char(src, pos);
	while (src[pos] && src[pos] != quote)
		pos ++;
	remove_char(src, pos);
	return (pos -1);
}

void	remove_negative_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == -'$')
			remove_char(str, i);
		else
			i ++;
	}
}

//this take a string, and remove any quote or assimilated around the token.
char	*trim_token(char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '\"')
			i = remove_quote(src, src[i], i);
		i ++;
	}
	remove_negative_char(src);
	return (src);
}
