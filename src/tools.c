/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 17:43:45 by bngo              #+#    #+#             */
/*   Updated: 2017/03/20 13:15:58 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			listlength(t_env *lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void		freetab(char **tab)
{
	int i;
	
	i = 0;
	while (tab[i])
	{
		if (tab[i])
			ft_strdel(&tab[i]);
		i++;
	}
	if (tab[i])
		ft_strdel(&tab[i]);
	tab = NULL;
	ft_putendl("-=[END OF FREETAB]=-");
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
