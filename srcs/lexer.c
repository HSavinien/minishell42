/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:44:32 by tmongell          #+#    #+#             */
/*   Updated: 2022/07/13 19:09:23 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//get_tokens : get the line and the index of the first char to handle. return the extracted token and set index to the index of the next char to handle.
static t_lst_token	*get_token(char *line, int *i, char **env)
{
	t_lst_token	*new;
	int			token_start;

	new = malloc(sizeof(t_lst_token));
	if (!new)
		error("unexpected malloc error");
	while (ft_isspace(line[*i]))
		*i ++;
	token_start = *i;
	while (line[*i] && !ft_isspace(line[*i]))
		*i+= lexer_checkcase(line + i, env);
	new->content = ft_substr(line, token_start, i - token_start);
	return (new);
}

static void	add_history(char *line)
{
	int	fd;

	fd = open(HISTORY, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd > 0)
		write(fd, line, ft_strlen(line));
	close(fd);
}

void	give_index(t_lst_token *lst)
{
	int	index;

	index = 0;
	while (lst)
	{
		lst->content = index ++;
		lst = lst->next;
	}
}

static t_lst_token	*lexing(char *line, char **env)
{
	int			i;
	t_lst_token	*tokens;
	t_lst_token	*last;

	if (!ft_strlen(line))
		return (NULL);
	add_history (line);
	line = expand_vars(line);
	tokens = get_token(line, &i, env);
	last = tokens;
	while (line[i])
	{
		last->next = get_token(line, &i);
		last = last->next;
	}
	last->next = NULL;
	give_index(tokens);
	return (tokens);
}
