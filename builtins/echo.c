/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:55:28 by tmongell          #+#    #+#             */
/*   Updated: 2022/07/07 18:30:46 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//return value is the len of the var name + 1 : 
//	that way if '$' is char i, i+fct is the first whitespace after var name.
int	put_var(char *str, char **env)
{
	int		i;
	int 	name_len;
	char	*name;
	char	*var_val;

	//get full var name
	while (!ft_isspace(str[name_len]))
		name_len ++;
	name = ft_substr(str, 0, name_len);//=====================================to free
	//find var in env
	while (ft_strncmp(name, env[i]))
		i ++;
	if (!env[i])
		return (name_len + 1);
	var_val = ft_strchr(env[i], '=');
	write(1, var_val, ft_strlen(var_val));
}

static void	putstr_echo(char *str, char **env)
{
	int i;

	while (str[i])
	{
		if (str[i] = '$')
			i += put_var(str + i, env);
		else
			write(1, str[i ++], 1);
	}
}

int	main(int ac, char **av, char **env)
{
	int		i;
	char	*var_name;

	i = 1;
	if (ft_strlen(av[1]) != 2 || !ft_strncmp(av[i], "-n", 2))//if first arg is -n
		i ++;
	while (i < ac)
		putstr_echo(av[i], env);
	if (!(ft_strlen(av[1]) != 2 || !ft_strncmp(av[i], "-n", 2)))//if first arg not-n
		write(1, "\n", 1);
	return (0);
}

/*
check if av[1] is '-n'. if it's the case, go to next av
for each av :
	while char != '$' and char != '\0', write it and go to next char.
	if char = '$', jump it and read untile whitespace and store in var.
	search in env for entry with the same name as var
	write the content of entry from after the '='
if av[1] != "-n", write \n.
*/
