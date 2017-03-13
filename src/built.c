/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:37:36 by bngo              #+#    #+#             */
/*   Updated: 2017/03/13 14:49:59 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			echo_func(char **str, t_globenv *envi)
{
	int i;
	int j;
	int	quot[2];

	i = 0;
	quot[0] = 0;
	quot[1] = 0;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == '\'' && quot[1] == 0)
				quot[0] = (quot[0] == 1) ? 0 : 1;
			if (str[i][j] == '"' && quot[0] == 0)
				quot[1] = (quot[1] == 1) ? 0 : 1;
			if ((str[i][j] == '\'' && quot[1]) || (str[i][j] == '"' && quot[0])
					|| (str[i][j] != '\'' && str[i][j] != '"'))
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
	char	*tmp2;
	char	*buff;

	path = NULL;
	buff = NULL;
	tmp2 = getlstvalue("PWD", envi);
	if (str[1])
	{
		ft_putendl("PATH1");
		if (str[1][0] == '~')
			path = pathhome(str[1], envi);
		else if (ft_strcmp(str[1], "-") == 0)
			path = getlstvalue("OLDPWD", envi);
		else if (str[1][0] != '/')
			path = trijoin(tmp2, "/", str[1]);
		else
			path = ft_strdup(str[1]);
	}
	else
		path = getlstvalue("HOME", envi);
	ft_putendl("TOTO");
	if (check_dir(path))
	{
		if (chdir(path) == 0)
		{
			update_vartab("OLDPWD", tmp2, envi);
			update_vartab("PWD", getcwd(buff, 512), envi);
		}
	}
	if (path)
		free(path);
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
