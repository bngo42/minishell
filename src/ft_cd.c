/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:11:22 by bngo              #+#    #+#             */
/*   Updated: 2017/03/23 15:33:28 by bngo             ###   ########.fr       */
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
	res = (char*)ft_memalloc(sizeof(char) * ft_strlen(path));
	while (i < len)
	{
		res[j++] = path[i++];
	}
	return (res);
}

void		setpath(char *path, char *old, t_globenv *envi)
{
	char	*buff;
	char	*tmp;

	buff = NULL;
	if (check_dir(path))
	{
		if (chdir(path) == 0)
		{
			tmp = getcwd(buff, 512);
			update_var("OLDPWD", old, envi);
			update_var("PWD", tmp, envi);
			ft_strdel(&tmp);
		}
	}
	if (buff)
		free(buff);
	if (path)
		ft_strdel(&path);
	if (old)
		ft_strdel(&old);
}
