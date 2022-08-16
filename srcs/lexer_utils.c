/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:11:48 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/16 16:07:32 by tmongell         ###   ########.fr       */
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
	{
		error("quotes not closed", 258, NULL);
		return (-1);
	}
	return (i + 1);
}

int	lexer_checkcase(char *line)
{
	if (line[0] == '\'' || line[0] == '\"' || line[0] == -('$'))
		return (handle_quote(line, line[0]));
	else
		return (1);
}

void	*lexer_error(char *line, t_lst_token *lst)
{
	free(line);
	destroy_lst(lst);
	return (NULL);
}
