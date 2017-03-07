/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:37:36 by bngo              #+#    #+#             */
/*   Updated: 2017/03/07 20:40:49 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			echo_func(char **str)
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

int			cd_func(char **str)
{
	ft_putendl("BUILTIN CD");
	return (0);
}

int			setenv_func(char **str)
{
	ft_putendl("BUILTIN SETENV");
	return (0);
}

int			unsetenv_func(char **str)
{
	ft_putendl("BUILTIN UNSETENV");
	return (0);
}

int			env_func(char **str)
{
	ft_putendl("BUILTIN ENV");
	return (0);
}

int			exit_func(char **str)
{
	ft_putendl("BUILTIN EXIT");
	return (0);
}
