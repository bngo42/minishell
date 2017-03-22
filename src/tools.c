/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 17:43:45 by bngo              #+#    #+#             */
/*   Updated: 2017/03/22 17:24:39 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			listlength(t_env *lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = lst;
	if (!tmp->next)
		return (1);
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

void		putlst(t_env *lst)
{
	t_env *tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->name)
		{
			ft_putstr(tmp->name);
			ft_putchar('=');
			ft_putstr(tmp->value);
			ft_putchar('\n');
		}
		tmp = tmp->next;
	}
}

void		changelvl(t_globenv *envi, int nb)
{
	char	*tmp;
	int		value;

	if ((tmp = getlstvalue("SHLVL", envi)) == NULL)
	{
		tmp = ft_strdup("0");
		newenv("SHLVL=1", envi);
	}
	value = ft_atoi(tmp);
	value += nb;
	ft_strdel(&tmp);
	tmp = ft_itoa(value);
	update_vartab("SHLVL", tmp, envi);
}
