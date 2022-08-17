/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:44:32 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/17 17:36:10 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define LOG_FILE "./lexer_log"

//check if the char nb i of str line should mark the end of a token, 
//and the start of a new token. it return 1 if it is an end token, 0 if it isnt
int	is_end_token(char *line, int i)
{
	if (line[i] == '\0')
		return (1);
	if (ft_isspace(line[i]))
		return (1);
	if (line[i] == '|')
		return (1);
	if (line[i] == '<')
		return (1);
	if (line[i] == '>')
		return (1);
	return (0);
}

t_lst_token	*get_special_token(char *line, int *i, t_lst_token *tok)
{
	int	len;
	int	start;

	start = *i;
	if (!line[*i])
		return (tok);
	if (line[*i + 1] == line [*i])
		len = 2;
	else
		len = 1;
	*i = *i + len;
	tok->content = ft_substr(line, start, *i - start);
	return (tok);
}

//get_tokens : get the line and the index of the first char to handle.
//return the extracted token and set index to the next char to handle.
static t_lst_token	*get_token(char *line, int *i)
{
	t_lst_token	*new;
	int			token_start;
	int			check_case;

	new = ft_calloc(sizeof(t_lst_token), 1);
	if (!new && tech_error("unexpected malloc error", 127, new))
		return (NULL);
	while (line[*i] && ft_isspace(line[*i]))
		*i += 1;
	if (!line[*i])
		return (ret_free(new));
	token_start = *i;
	if (line[*i] == '|' || line[*i] == '<' || line[*i] == '>' || !line[*i])
		return (get_special_token(line, i, new));
	while (line[*i] && !is_end_token(line, *i))
	{
		check_case = lexer_checkcase(line + *i);
		if (check_case == -1)
			return (ret_free(new));
		*i = *i + check_case;
	}
	new->content = ft_substr(line, token_start, *i - token_start);
	return (new);
}

int	get_each_token(t_lst_token *tokens, char *line, int i)
{
	int			error;
	t_lst_token	*last;

	error = 0;
	last = tokens;
	while (line[i])
	{
		last->next = get_token(line, &i);
		if (!last->next)
		{
			error = 1;
			break ;
		}
		if (!last->next->content)
			break ;
		last = last->next;
	}
	last->next = NULL;
	return (error);
}

t_lst_token	*lexing(char *line)
{
	int			i;
	int			error;
	t_lst_token	*tokens;

	i = 0;
	g_varvalues.ret = 0;
	if (!line || !ft_strlen(line))
		return (lexer_error(line, NULL));
	tokens = get_token(line, &i);
	if (!tokens)
		return (lexer_error(line, NULL));
	error = get_each_token(tokens, line, i);
	if (error && g_varvalues.ret)
		return (lexer_error(line, tokens));
	give_index(tokens);
	free(line);
	return (tokens);
}
