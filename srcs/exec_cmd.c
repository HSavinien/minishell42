/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:58:47 by tmongell          #+#    #+#             */
/*   Updated: 2022/08/15 16:22:17 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	try_path(char *cmd, char *path, char **args, char **env)
{
	char	*cmd_path;

	path = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(path, cmd);
	free(path);
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
		exit(error("cmd not found (no PATH)", 127, NULL));
	path = ft_split(ft_strchr(env[i], '=') + 1, ':');
	if (!*path)
		exit(error("cmd not found (PATH empty)", 127, NULL));
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
		return (destroy_array(args));
	pid = fork();
	if (!pid)
	{
		execve(cmd, args, env);
		path = get_path(env);
		i = 0;
		while (path[i])
			try_path(cmd, path[i ++], args, env);
		destroy_array(path);
		exit(error("command not found", 127, NULL));
	}
	waitpid(pid, &i, 0);
	if (i == SIGINT)
		g_varvalues.ret = i + 128;
	else
		g_varvalues.ret = WEXITSTATUS(i);
	close(1);
	return (destroy_array(args));
}
