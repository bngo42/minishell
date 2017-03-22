/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:30:48 by bngo              #+#    #+#             */
/*   Updated: 2017/03/22 19:31:11 by bngo             ###   ########.fr       */
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
		ft_putendl("TOTO");
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
		if (execve(path, arg, env))
		{
			freetab(env);
			return (1);
		}
		else
			return (0);
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
	else
	{
		if ((path = get_cmd_path(envi)))
		{
			while (path[++i] && ret)
			{
				newpath = ft_strjoin(path[i], "/");
					newcmd = ft_strjoin(newpath, cmd);
				if (access(newcmd, F_OK) == 0)
					ret = exe_cmd(newcmd, arg, envi);
				free(newcmd);
				free(newpath);
			}
			freetab(path);
		}
	}
	return (ret);
}
