/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 19:24:30 by cmaroude          #+#    #+#             */
/*   Updated: 2022/08/10 20:11:27 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exchange_path_pwd(char *str)
{
	char	*pwd;
	int		index_var;
	char	*var_new;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories:", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (EXIT_FAILURE);
	}
	index_var = ft_find_index(g_varvalues.env, str, ft_strlen(str));
	var_new = ft_strjoin(str, pwd);
	if (index_var == -1)
		ft_add_env(var_new, 0);
	if (index_var == -1 || !g_varvalues.env[index_var])
		return (EXIT_SUCCESS);
	free(g_varvalues.env[index_var]);
	g_varvalues.env[index_var] = var_new;
	return (EXIT_SUCCESS);
}

char	*ft_get_path(char **env, char *env_srch, int len_srch)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], env_srch, len_srch))
			i++;
	path = &env[i][len_srch];
	if (!path)
		return (NULL);
	else
		return (path);
}

int	ft_chdir(char *path, char *str)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (EXIT_FAILURE);
	}
	if (!ft_exchange_path_pwd("OLDPWD="))
		ft_exchange_path_pwd("PWD=");
	return (EXIT_SUCCESS);
}

int	ft_cd(int argc, char **argv)
{
	char	*path;

	if (argc == 1)
	{
		path = ft_get_path(g_varvalues.env, "HOME=", ft_strlen("HOME="));
		if (!path)
		{	
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putendl_fd(strerror(errno), 2);
			return (EXIT_FAILURE);
		}
		return (ft_chdir(path, argv[0]));
	}
	else
		return (ft_chdir(argv[1], argv[1]));
	return (EXIT_SUCCESS);
}
