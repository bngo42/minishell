/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 17:43:45 by bngo              #+#    #+#             */
/*   Updated: 2017/03/08 18:19:34 by bngo             ###   ########.fr       */
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

void		freetab(char ***tab)
{
	int i;
	
	i = 0;
	while (*tab[i])
	{
		ft_strdel(&(*tab[i]));
		i++;
	}
	free(*tab);
	*tab = NULL;
}

void		freelst(t_env **lst)
{
	t_env *tmp;

	tmp = *lst;
	*lst = (*lst)->next;
	while (tmp)
	{
		ft_strdel(&tmp->name);
		ft_strdel(&tmp->value);
		tmp->next = NULL;
		free(tmp);
		tmp = *lst;
		*lst = (*lst)->next;
	}
}

void		update_env(char **env, t_env *lst)
{
	int		i;
	char	**newenv;
	char	*var;
	t_env	*tmp;

	i = 0;
	newenv = NULL;
	tmp = lst;
	if (!(newenv = (char**)malloc(sizeof(char*) * listlength(lst) + 1)))
		return ;
	while (tmp->next)
	{
		var = ft_strjoin(tmp->name, tmp->value);
		newenv[i] = ft_strdup(var);
		free(var);
		free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		tmp = tmp->next;
		i++;
	}
	freelst(&lst);
}