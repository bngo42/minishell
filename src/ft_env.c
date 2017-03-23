/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:14:21 by bngo              #+#    #+#             */
/*   Updated: 2017/03/23 13:19:08 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			update_envtab(t_globenv *envi)
{
	t_env	*tmp;
	char	**res;
	int		i;

	i = 0;
	if (!(res = (char**)ft_memalloc(sizeof(char*) * listlength(envi->envlst))))
		return (-1);
	tmp = envi->envlst;
	while (tmp)
	{
		res[i++] = trijoin(tmp->name, "=", tmp->value);
		tmp = tmp->next;
	}
	res[i] = 0;
	freetab(envi->envtab);
	envi->envtab = ft_cpytab(res);
	freetab(res);
	return (0);
}

int			newenv(char *str, t_globenv *envi)
{
	char	**tmp;
	t_env	*newlink;

	tmp = NULL;
	newlink = NULL;
	if (!(tmp = ft_strsplit(str, '=')))
		return (-1);
	if (!(update_var(tmp[0], tmp[1], envi)))
	{
		if (!(newlink = (t_env*)ft_memalloc(sizeof(t_env))))
			return (-1);
		if (tmp[0])
		{
			newlink->name = ft_strdup(tmp[0]);
			newlink->value = (tmp[1]) ? ft_strdup(tmp[1]) : ft_strnew(0);
			newlink->next = NULL;
			newlink->prev = NULL;
			add_env(&envi->envlst, newlink);
		}
	}
	freetab(tmp);
	return (0);
}
