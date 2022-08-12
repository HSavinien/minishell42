/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:58:47 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/12 15:51:59 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	try_path(char *cmd, char *path, char **args, char **env)
{
	char	*cmd_path;

	cmd_path = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(cmd_path, cmd);
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
		error ("cmd not found (no PATH)");
	path = ft_split(ft_strchr(env[i], '=') + 1, ':');
	if (!*path)
		error ("cmd not found (PATH empty)");
	return (path);
}

//function that execute a cmd and it's args. 
//it first try to execute it as a builtin, then try with execve
//it always return 0, because the function that call it need a int function.
int	exec_cmd(char	*cmd, char **args, char **env)
{
	char	**path;
	int		pid;
	int		i;

	if (!cmd || try_builtins(args))
		return (0);
	pid = fork();
	if (!pid)
	{
		execve(cmd, args, env);
		path = get_path(env);
		i = 0;
		while (path[i])
			try_path(cmd, path[i ++], args, env);
		error("command not found");
		return (0);
	}
	waitpid(pid, &i, 0);
	if (i == SIGINT)
		g_varvalues.ret = i + 128;
	else
		g_varvalues.ret = WEXITSTATUS(i);
	close(1);
	return (0);
}
