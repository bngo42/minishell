/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:14:21 by bngo              #+#    #+#             */
/*   Updated: 2017/03/21 14:08:42 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			update_envtab(t_globenv *envi)
{
	t_env	*tmp;
	char	**res;
	int		i;

	i = 0;
	ft_putendl("[START UPDATE ENVTAB]");
	if (!(res = (char**)malloc(sizeof(char*) * listlength(envi->envlst))))
		return (-1);
	ft_putendl("[MALLOC NEW TAB]");
	tmp = envi->envlst;
	while (tmp)
	{
		res[i++] = trijoin(tmp->name, "=", tmp->value);
		tmp = tmp->next;
	}
	res[i] = 0;
	ft_putendl("[COPY IN NEW TAB]");
	freetab(envi->envtab);
	ft_putendl("[FREE ENVTAB]");
	envi->envtab = ft_cpytab(res);
	return (0);
}
/*
int			newenv(char *str, t_globenv *envi)
{
	char	**tmp;
	t_env	*newlink;

	tmp = NULL;
	if (!(tmp = ft_strsplit(str, '=')))
		return (-1);
	if (!(newlink = (t_env*)malloc(sizeof(t_env))))
		return (-1);
	if (update_vartab(tmp[0], tmp[1], envi) == 0)
	{
	printf("Updating env with [%s] => [%s]\n", tmp[0], tmp[1]);
		newlink->name = ft_strdup(tmp[0]);
	ft_putendl("DUPLICATE TMP 0");
		newlink->value = (tmp[1]) ? ft_strdup(tmp[1]) : ft_strnew(0);
	newlink->next = NULL;
	ft_putendl("DUPLICATE TMP !");
		add_env(&envi->envlst, newlink);
	ft_putendl("ADD ENV");
		freetab(tmp);
	ft_putendl("FREETAB tmp");
		update_envtab(envi);
	ft_putendl("UPDATE ENVTAB");
	}
	return (0);
}
*/
int			newenv(char *str, t_globenv *envi)
{

	return (0);
}
