#include "../minishell.h"

//find the longest var in env, and return it's len.
//maxlen start at 3 because $? is 3 digit long max.
int	max_var_len(char **env)
{
	int	i;
	int	max_len;
	int	tmp_len;

	max_len = 3;
	i = 0;
	while(env[i])
	{
		tmp_len = ft_strlen(env[i ++]);
		if (tmp_len > max_len)
			max_len = tmp_len;
	}
	return (max_len + 2);
}

//get a wide estimate of the size of the expanded linei. 
//it will always alocate wider than necessary, cause we don't want no segfault
char	*alocate_line(char *src, char **env)
{
	int	i;
	int	nb_var;

	i = 0;
	nb_var = 0;
	while (src[i])
	{
		if (src[i ++] == '$')
			nb_var ++;
	}
	nb_var *= max_var_len(env);
	return (ft_calloc(i + nb_var, sizeof(char)));
}

//the main function malloc more memory than needed, this function get ride of
//any unnecessary alocated byte
char	*opti_line(char *src)
{
	char	*opti;

	opti = ft_strdup(src);
	free (src);
	return (opti);
}

//read a string from the '$' symbole in pos i up to next space/special char,
//and return the resulting substr. also incremente i to bring it to said 
//stoping char.
char	*get_var_name(char *src, int *i)
{
	int	len;
	int	start;

	start = *i; //jump the '$' char
	start ++;
	len = 0;
	while (src[*i] && !ft_isspace(src[*i])) {
		len ++;
		*i = *i + 1;
	}
	return(ft_substr(src, start, len - 1));
}

//search a var of given name in env, and write it's value in dst.
//for lexer purpose, the value is writen between double quote.
int		copy_var(char *var_name, char *dst, char **env)
{
	int		i;
	int		j;
	int		namelen;
	char	*tmp_str;

	tmp_str = ft_strjoin(var_name, "=");
	namelen = ft_strlen(tmp_str);
	i = 0;
	while (env[i] && strncmp(env[i], tmp_str, namelen)) {
		i ++;
	}
	free (tmp_str);
	if (!env[i])
		return (0);
	tmp_str = ft_strchr(env[i], '=') + 1;
	j = 0;
	i = 0;
	dst[j ++] = -'$';
	while (tmp_str[i])
		dst[j ++] = tmp_str[i ++];
	dst[j ++] = -'$';
	return (j);
}

//first step of parsing : take a str, replace var name by their value, and 
//return the result. since the line to read is freed, it should have been 
//alocated with malloc beforehand.
char	*expand_vars(char *src, char **env)
{
	int		quote_on;
	char	*final_line;
	char	*var_name;
	int		i;
	int		j;

	quote_on = 0;
	i = 0;
	j = 0;
	final_line = alocate_line(src, env);
	while (src[i])
	{
		if (src[i] == '\'')
			quote_on = quote_on + 1 % 2;
		if (src[i] == '$' && !quote_on && src[i - 1] != '\\')
		{
			var_name = get_var_name(src, &i);
			j += copy_var(var_name, final_line + j, env);
			free(var_name);
		}
		else
			final_line[j ++] = src[i ++];
	}
	free (src);
	return (opti_line(final_line));
}
