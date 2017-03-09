/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:11:22 by bngo              #+#    #+#             */
/*   Updated: 2017/03/09 20:18:06 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			check_dir(char *path)
{
	struct stat		filestat;

	printf("Checking [%s]\n", path);
	if (lstat(path, &filestat) == 0)
		ft_putendl("[FILE]");
	else if (opendir(path))
		ft_putendl("[directory]");
	ft_putendl("cd: not such file or directory: [FILENAME]");
	return (1);
}
