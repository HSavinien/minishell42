/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:31:57 by cmaroude          #+#    #+#             */
/*   Updated: 2022/07/08 19:34:31 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef BIN_DIR
#  define BIN_DIR "./minishell/bin"
# endif

# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "library/libft/libft.h"
# include "library/get_next_line/get_next_line.h"

int		main();
void	cmd_exec(char	*fct, char **env);

#endif
