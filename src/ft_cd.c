/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:11:22 by bngo              #+#    #+#             */
/*   Updated: 2017/03/13 13:03:47 by bngo             ###   ########.fr       */
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
		{
			ft_putstr("cd: not a directory: ");
			ft_putendl("[FILENAME]");
		}
	}
	else
	{
		ft_putstr("cd: not such file or directory: ");
		ft_putendl("[FILENAME]");
	}
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
