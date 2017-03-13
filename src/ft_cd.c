/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:11:22 by bngo              #+#    #+#             */
/*   Updated: 2017/03/13 20:36:47 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			check_dir(char *path)
{
	struct stat		filestat;

	if (stat(path, &filestat) == 0)
	{
		if (filestat.st_mode & S_IFDIR)
			return (1);
		else if (filestat.st_mode & S_IFREG)
			ft_putendl("cd: not a directory");
	}
	else
		ft_putendl("cd: not such file or directory");
	return (0);
}

char		*pathhome(char *path, t_globenv *envi)
{
	char	*newpath;
	char	*tmp;

	newpath = NULL;
	if (path && path[0] == '~')
	{
		tmp = getlstvalue("HOME", envi);
		path++;
		newpath = ft_strjoin(tmp, path);
		if (tmp)
			free(tmp);
		ft_putendl(newpath);
	}
	return (newpath);
}


char		*filterpath(char *path)
{
	char	*res;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(path);
	if (path[len] == '/')
		len--;
	res = (char*)malloc(sizeof(char) * ft_strlen(path));
	while (i < len)
	{
			res[j++] = path[i++];
	}
	return (res);
}

char		*redirect(char *path)
{
	char	**tmp;
	char	*res;
	char	*tmp2;
	int		i;
	int		j;

	i = -1;
	res = NULL;
	if ((tmp = ft_strsplit(path, '/')))
	{
		while (tmp[++i])
		{
			if (ft_strcmp(tmp[i], "..") == 0)
			{
				j = i;
				while (j > 0 && tmp[j] == 0)
					j--;
				tmp[i] = 0;
				tmp[j] = 0;
			}
		}
		j = 0;
		while (j < i)
		{
			if (tmp[j])
			{
				tmp2 = trijoin(res,"/", tmp[j]);
				res = ft_strdup(tmp2);
				if (tmp2)
					free(tmp2);
			}
			j++;
		}
	}
	return (res);
}

void		setpath(char *path, char *old, t_globenv *envi)
{
	char	*buff;

	buff = NULL;
	if (check_dir(path))
	{
		if (chdir(path) == 0)
		{
			update_vartab("OLDPWD", old, envi);
			update_vartab("PWD", redirect(path), envi);
		}
	}
}




