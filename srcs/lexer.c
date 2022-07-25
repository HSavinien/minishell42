/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:44:32 by tmongell          #+#    #+#             */
/*   Updated: 2022/07/25 14:50:36 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define HISTORY "./lexer_log"

#include "../minishell.h"

//filler function
void	error(char *msg)
{
	printf("Error : %s\n", msg);
	exit(42);
}

//get_tokens : get the line and the index of the first char to handle. return the extracted token and set index to the index of the next char to handle.
static t_lst_token	*get_token(char *line, int *i)
{
	t_lst_token	*new;
	int			token_start;

	new = malloc(sizeof(t_lst_token));
	if (!new)
		error("unexpected malloc error");
	while (ft_isspace(line[*i]))
		*i += 1;
	token_start = *i;
	while (line[*i] && !ft_isspace(line[*i]))
		*i = *i + lexer_checkcase(line + *i);
	new->content = ft_substr(line, token_start, *i - token_start);
	new->content = trim_token(new->content);
	return (new);
}

static void	add_logfile(char *line)
{
	int	fd;

	fd = open(HISTORY, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd > 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	close(fd);
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

t_lst_token	*lexing(char *line, char **env)
{
	int			i;
	t_lst_token	*tokens;
	t_lst_token	*last;

	i = 0;
	if (!ft_strlen(line))
		return (NULL);
	add_logfile (line);//break stuff for some reason
	line = expand_vars(line, env);
	printf("expanded line : %s\n", line);//debug
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
