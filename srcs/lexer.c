/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:44:32 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/09 19:19:10 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define LOG_FILE "./lexer_log"

//get_tokens : get the line and the index of the first char to handle. return the extracted token and set index to the index of the next char to handle.
static t_lst_token	*get_token(char *line, int *i)
{
	t_lst_token	*new;
	int			token_start;

	new = malloc(sizeof(t_lst_token));
	if (!new)
		error("unexpected malloc error");
	while (line[*i] && ft_isspace(line[*i]))
		*i += 1;
	token_start = *i;
	while (line[*i] && !ft_isspace(line[*i]))
		*i = *i + lexer_checkcase(line + *i);
	new->content = ft_substr(line, token_start, *i - token_start);
	return (new);
}

void	give_index(t_lst_token *lst)
{
	int	index;

	index = 0;
	while (lst)
	{
		lst->index = index ++;
		lst = lst->next;
	}
}

t_lst_token	*lexing(char *line)
{
	int			i;
	t_lst_token	*tokens;
	t_lst_token	*last;

	i = 0;
	if (!line || !ft_strlen(line))
		return (NULL);
	tokens = get_token(line, &i);
	last = tokens;
	while (line[i])
	{
		last->next = get_token(line, &i);
		last = last->next;
	}
	last->next = NULL;
	give_index(tokens);
	free(line);
	return (tokens);
}
