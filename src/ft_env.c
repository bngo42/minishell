/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:14:21 by bngo              #+#    #+#             */
/*   Updated: 2017/03/16 15:26:07 by bngo             ###   ########.fr       */
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
	envi->envtab = res;
	return (0);
}

int			newenv(char *str, t_globenv *envi)
{
	char	**tmp;
	t_env	*newlink;

	tmp = NULL;
	if (!(tmp = ft_strsplit(str, '=')) || !tmp[0])
		return (-1);
	if (!(newlink = (t_env*)malloc(sizeof(t_env))))
		return (-1);
	if (update_vartab(tmp[0], tmp[1], envi) == 0)
	{
	printf("Updating env with [%s] => [%s]\n", tmp[0], tmp[1]);
		newlink->name = ft_strdup(tmp[0]);
		newlink->value = ft_strdup(tmp[1]);
	ft_putendl("DEBUG");
		add_env(&envi->envlst, newlink);
		freetab(tmp);
		update_envtab(envi);
	}
	ft_putendl("DEBUG");
	return (0);
}

