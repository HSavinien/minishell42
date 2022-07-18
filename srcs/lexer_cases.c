/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:11:48 by tmongell          #+#    #+#             */
/*   Updated: 2022/07/13 19:47:23 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_quote(char *line, char quote)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != quote)
		i ++;
	if (!line[i])
		error("quotes not closed");
	return (i);
}

int	lexer_checkcase(char	*line)
{
	if (line[0] == ''' || line[0] == '"')
		return (handle_quote(line, line[0]));
	else if (line[0] == '\\')
		return (2);
	else
		return (1);
}

