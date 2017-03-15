/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:30:48 by bngo              #+#    #+#             */
/*   Updated: 2017/03/15 17:19:26 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		**get_cmd_path(t_globenv *envi)
{
	char	**tmp;
	char	**path;
	int		i;

	path = NULL;
	i = 0;
	while (envi->envtab[i])
	{
		tmp = NULL;
		if ((tmp = ft_strsplit(envi->envtab[i], '=')))
		{
			if (tmp[0] && ft_strcmp(tmp[0], "PATH") == 0)
			{
				path = ft_strsplit(tmp[1], ':');
				freetab(tmp);
				return (path);
			}
			freetab(tmp);
		}
		i++;
	}
	return (path);
}

int			exe_cmd(char *path, char **arg, t_globenv *envi)
{
	pid_t	process;

	process = fork();
	if (process == 0)
	{
		if (execve(path, arg, envi->envtab))
			return (1);
		else
			return (0);
	}
	else
		wait (NULL);
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
	if (!access(cmd, F_OK))
		ret = exe_cmd(cmd, arg, envi);
	else
	{
		path = get_cmd_path(envi);
		while (path[++i] && ret)
		{
			newpath = ft_strjoin(path[i], "/");
			newcmd = ft_strjoin(newpath, cmd);
			if (!access(newcmd, F_OK))
				ret = exe_cmd(newcmd, arg, envi);
			if (newcmd)
				free(newcmd);
			if (newpath)
				free(newpath);
		}
	}
	if (path)
		freetab(path);
	return (ret);
}
