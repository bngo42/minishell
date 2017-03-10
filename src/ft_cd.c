/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:11:22 by bngo              #+#    #+#             */
/*   Updated: 2017/03/10 16:17:43 by bngo             ###   ########.fr       */
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
		free(tmp);
		ft_putendl(newpath);
	}
	return (newpath);
}
