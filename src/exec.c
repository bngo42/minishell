/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:30:48 by bngo              #+#    #+#             */
/*   Updated: 2017/03/07 20:18:57 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			check_path(char *str)
{
	int i;
	int j;
	int state;
	char *path;

	i = ft_strlen(str);
	j = 0;
	state = 0;
	path = NULL;
	while (i > 0 && str[i - 1] != '/')
		i--;
	if (i <= 0)
		return (state);
	else
	{
		path = ft_strsub(str, 0, i);
		if (ft_strcmp(path, "/bin/") == 0)
			state = 1;
	}
	if (path)
		free(path);
	return (state);
}

char		**get_cmd_path(char **env)
{
	char	**tmp;
	char	**path;
	int		i;

	path = NULL;
	i = 0;
	while (env[i])
	{
		tmp = NULL;
		if ((tmp = ft_strsplit(env[i], '=')))
		{
			if (tmp[0] && ft_strcmp(tmp[0], "PATH") == 0)
				path = ft_strsplit(tmp[1], ':');
		}
		if (tmp)
			free(tmp);
		i++;
	}
	return (path);
}

int			check_cmd(char *cmd, char **arg, char **env)
{
	int		i;
	char	**path;
	char	*newcmd;
	char	*newpath;

	i = -1;
	if (!check_path(cmd))
	{
		path = get_cmd_path(env);
		while (path[++i])
		{
			newpath = ft_strjoin(path[i], "/");
			newcmd = ft_strjoin(newpath, cmd);
			if (execve(newcmd, arg, env) != -1)
				return (1);
			if (newcmd)
				free(newcmd);
			if (newpath)
				free(newpath);
		}
		return (-1);
	}
	else if (execve(cmd, arg, env) == -1)
		return (-1);
	return (-1);
}
