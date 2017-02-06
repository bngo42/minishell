/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:37:36 by bngo              #+#    #+#             */
/*   Updated: 2017/02/06 14:34:24 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			echo_func(char **str)
{
	int i;
	int j;
	int simple;
	int doublle;

	i = 0;
	simple = 0;
	doublle = 0;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == '\'' && doublle == 0)
				simple = (simple == 1) ? 0 : 1;
			if (str[i][j] == '"' && simple == 0)
				doublle = (doublle == 1) ? 0 : 1;
			if ((str[i][j] == '\'' && doublle) || (str[i][j] == '"' && simple)
					|| (str[i][j] != '\'' && str[i][j] != '"'))
			ft_putchar(str[i][j]);
		}
		ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}
