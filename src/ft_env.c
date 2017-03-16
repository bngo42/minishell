/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:14:21 by bngo              #+#    #+#             */
/*   Updated: 2017/03/16 14:05:04 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			newenv(char *str, t_globenv *envi)
{
	char	**tmp;
	t_env	*newlink;

	tmp = NULL;
	if (!(ft_strsplit(str, '=')))
		return (-1);
	newlink->name = tmp[0];
	newlink->value = tmp[1];
	add_env(&envi->envlst, newlink);
	freetab(tmp);
	return (0);
}
