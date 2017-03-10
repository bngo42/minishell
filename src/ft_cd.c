/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:11:22 by bngo              #+#    #+#             */
/*   Updated: 2017/03/10 13:04:53 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			check_dir(char *path)
{
	struct stat		filestat;

	if (stat(path, &filestat) >= 0)
	{
		if (filestat.st_mode & S_IFDIR)
			return (1);
		else if (filestat.st_mode & S_IFREG)
		{
			ft_putendl("cd: not a directory: [FILENAME]");
		}
	}
	else
		ft_putendl("cd: not such file or directory: [FILENAME]");
	return (0);
}
