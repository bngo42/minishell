/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:14:21 by bngo              #+#    #+#             */
/*   Updated: 2017/03/22 12:58:02 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			update_envtab(t_globenv *envi)
{
	t_env	*tmp;
	char	**res;
	int		i;

	i = 0;
	if (!(res = (char**)malloc(sizeof(char*) * listlength(envi->envlst))))
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
	ft_putendl("VALUE SPLITTED");
	if (!(newlink = (t_env*)malloc(sizeof(t_env))))
		return (-1);
	ft_putendl("NEWLINK ALLOCATED");
	newlink->name = ft_strdup(tmp[0]);
	newlink->value = (tmp[1]) ? ft_strdup(tmp[1]) : ft_strnew(0);
	newlink->next = NULL;
	ft_putendl("VALUE COPIED");
	add_env(&envi->envlst, newlink);
	ft_putendl("NEW LINK ADDED");
	freetab(tmp);
	return (0);
}
