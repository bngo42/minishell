/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 17:43:45 by bngo              #+#    #+#             */
/*   Updated: 2017/03/16 14:18:34 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			listlength(t_env *lst)
{
	int i;

	i = 0;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void		freetab(char **tab)
{
	int i;
	
	i = 0;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	if (tab)
		free(tab);
	tab = NULL;
}

void		freelst(t_env **lst)
{
	t_env *tmp;

	if (lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		while (tmp->next)
		{
			ft_strdel(&tmp->name);
			ft_strdel(&tmp->value);
			tmp->next = NULL;
			free(tmp);
			tmp = *lst;
			*lst = (*lst)->next;
		}
	}
}
