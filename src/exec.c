/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:30:48 by bngo              #+#    #+#             */
/*   Updated: 2017/03/24 17:39:22 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		**get_cmd_path(t_globenv *envi)
{
	char	**path;
	char	*tmp;

	path = NULL;
	tmp = NULL;
	if ((tmp = getlstvalue("PATH", envi)))
	{
		path = ft_strsplit(tmp, ':');
		ft_strdel(&tmp);
		return (path);
	}
	return (path);
}

int			exe_cmd(char *path, char **arg, t_globenv *envi)
{
	pid_t	process;
	char	**env;

	process = fork();
	if (process == 0)
	{
		env = convert_lst(envi->envlst);
		execve(path, arg, env);
	}
	else
		wait(NULL);
	return (0);
}

int			check_cmd(char *cmd, char **arg, t_globenv *envi)
{
	int		i;
	char	**path;
	char	*newcmd;
	char	*newpath;
	int		ret;

	i = -1;
	ret = 1;
	path = NULL;
	if (access(cmd, F_OK) == 0)
		ret = exe_cmd(cmd, arg, envi);
	else if ((path = get_cmd_path(envi)))
	{
		while (path[++i] && ret)
		{
			newcmd = trijoin(path[i], "/", cmd);
			if (access(newcmd, F_OK) == 0)
				ret = exe_cmd(newcmd, arg, envi);
			free(newcmd);
		}
		freetab(path);
	}
	return (ret);
}
