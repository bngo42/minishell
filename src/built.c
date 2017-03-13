/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:37:36 by bngo              #+#    #+#             */
/*   Updated: 2017/03/13 18:33:40 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		printenv(char *str, t_globenv *envi)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;

	i = 0;
	j = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	tmp = ft_strsub(str, 0, i);
	tmp2 = getlstvalue(tmp, envi);
	ft_putendl(tmp2);
	if (tmp)
		free(tmp);
	if (tmp2)
		free(tmp2);
}

int			echo_func(char **str, t_globenv *envi)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == '$')
			{
				k = 0;
				while (str[i][j + k] != ' ' && str[i][j + k] != '\t')
					k++;
				tmp = ft_strsub(str[i], j, k);
				tmp = getlstvalue(tmp, envi);
			}
			if (tmp)
				ft_putstr(tmp);
			else
				ft_putchar(str[i][j]);
		}
		if (str[i + 1])
			ft_putchar(' ');
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
	if (str[1])
	{
		if (str[1][0] == '~')
			path = pathhome(str[1], envi);
		else if (ft_strcmp(str[1], "-") == 0)
			path = getlstvalue("OLDPWD", envi);
		else if (str[1][0] != '/')
			path = trijoin(tmp, "/", str[1]);
		else
			path = ft_strdup(str[1]);
	}
	else
		path = getlstvalue("HOME", envi);
	setpath(path, tmp, envi);
	if (path)
		free(path);
	if (tmp)
		free(tmp);
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
	t_env *tmp;

	tmp = envi->envlst;
	if (str[1] && ft_strcmp(str[1], "-i") == 0)
		ft_putchar('i');
	else if (str[1] && ft_strcmp(str[1], "-v") == 0)
		ft_putchar('i');
	else
	{
		while (tmp)
		{
			ft_putstr(tmp->name);
			ft_putchar('=');
			ft_putendl(tmp->value);
			tmp = tmp->next;
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
