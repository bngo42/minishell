/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:37:36 by bngo              #+#    #+#             */
/*   Updated: 2017/03/16 13:01:29 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		echo_func(char **str, t_globenv *envi)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_putendl(str[i]);
		if (str[i + 1])
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (0);
}

int			cd_func(char **str, t_globenv *envi)
{
	char	*path;
	char	*tmp;
	char	*buff;

	path = NULL;
	buff = NULL;
	tmp = getlstvalue("PWD", envi);
	if (str[1] && str[1][0] == '~')
		path = pathhome(str[1], envi);
	else if (str[1] && ft_strcmp(str[1], "-") == 0)
	{
		path = getlstvalue("OLDPWD", envi);
		ft_putendl(path);
	}
	else if (str[1] && str[1][0] != '/')
		path = trijoin(tmp, "/", str[1]);
	else if (str[1])
		path = ft_strdup(str[1]);
	else
		path = getlstvalue("HOME", envi);
	setpath(path, tmp, envi);
	return (0);
}

int			setenv_func(char **str, t_globenv *envi)
{
	ft_putendl("BUILTIN SETENV");
	return (0);
}

int			unsetenv_func(char **str, t_globenv *envi)
{
	ft_putendl("BUILTIN UNSETENV");
	return (0);
}

int			env_func(char **str, t_globenv *envi)
{
	int		i;
	int		j;

	i = 0;
	while (str[++i])
	{
		if (check_cmd(str[i], &str[i], envi) == 0)
			return (0);
	}
	i = 0;
	showtab(envi->envtab);
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == '=')
			{
				if (str[i][j - 1] != '=' && j > 0)
					ft_putendl(str[i]);
				else
				{
					ft_putstr("BOBI-MISHELL: ");
					ft_putstr(str[i]);
					ft_putendl(" not found");
					return (0);
				}
			}
		}
	}
	return (0);
}

int			exit_func(char **str, t_globenv *envi)
{
	int i;
	int e;

	i = 0;
	e = 0;
	while (str[i])
		i++;
	if (i > 2)
		ft_putendl("exit: too many arguments");
	else
	{
		if (str[1])
			e = atoi(str[1]);
		exit( (e < 256) ? e : 0);
	}
	return (0);
}
