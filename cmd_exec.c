/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:42:46 by tmongell          #+#    #+#             */
/*   Updated: 2022/07/08 20:14:01 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	try_path(char *cmd, char *path, char **args, char **env)
{
	char	*cmd_path;
			
	cmd_path = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(cmd_path, fct);
	execve(cmd_path, args, env);
	free(cmd_path);
}

char	**get_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i ++;
	if (!env[i])
		error ("cmd not found (no PATH)");//might need correction
	path = ft_split(ft_strchr(env[i], '=') + 1, ':');
	if (!*path)
		error ("cmd not found (PATH empty)");//might need correction
	return (path);
}

void	do_cmd(char	*fct, char **env)
{
	char	**path;
	char	*cmd_path;
	char	**args;
	int		pid;
	int		i;

	pid = fork();
	if (!pid)
	{
		fct = extract_args(fct, &args);
		execve(fct, args, env);
		try_path(fct, BIN_DIR, args, env);
		path = get_path(env);
		i = 0;
		while (path[i])
		{
			cmd_path = ft_strjoin(path[i ++], "/");
			cmd_path = ft_strjoin(cmd_path, fct);
			execve(cmd_path, args, env);
			free(cmd_path);
		}
		error("comande not found");//might need correction
	}
	else
		waitpid(pid, &i, 0);
}
