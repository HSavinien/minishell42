/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:58:47 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/09 14:57:17 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	try_path(char *cmd, char *path, char **args, char **env)
{
//	dprintf(2, "entering %s\n", __FUNCTION__);//debug
	char	*cmd_path;
			
	cmd_path = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(cmd_path, cmd);
	execve(cmd_path, args, env);
	free(cmd_path);
//	dprintf(2, "exiting %s\n", __FUNCTION__);//debug
}

char	**get_path(char **env)
{
//	dprintf(2, "entering %s\n", __FUNCTION__);//debug
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
//	dprintf(2, "exiting %s\n", __FUNCTION__);//debug
	return (path);
}

void	exec_cmd(char	*cmd, char **args, char **env)
{
	char	**path;
	int		pid;
	int		i;

	if (try_builtins(args))
		return;
	pid = fork();
	if (!pid)
	{
		execve(cmd, args, env);
		path = get_path(env);
		i = 0;
		while (path[i])
			try_path(cmd, path[i ++], args, env);
		error("comande not found");
	}
	else
	{
		waitpid(pid, &i, 0);
		g_varvalues.ret = WEXITSTATUS(i);
		close(1);
	}
	return;
}
