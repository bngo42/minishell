/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:29:45 by bngo              #+#    #+#             */
/*   Updated: 2017/03/09 18:35:39 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*getlstvalue(char *name, t_globenv *envi)
{
	t_env	*tmp;
	char	*res;

	res = NULL;
	tmp = envi->envlst;
	while (tmp && ft_strcmp(name, tmp->name) != 0)
		tmp = tmp->next;
	if (tmp->value)
		res = ft_strdup(tmp->value);
	return (res);
}

char		*gettabvalue(char *name, t_globenv *envi)
{
	char	*res;
	char	**tmp;
	int		i;

	res = NULL;
	i = 0;
	while (envi->envtab[i])
	{
		tmp = ft_strsplit(envi->envtab[i], '=');
		if (ft_strcmp(name, tmp[0]) == 0)
		{
			if (tmp[1])
				res = ft_strdup(tmp[1]);
		}
		ft_strdel(&tmp[0]);
		ft_strdel(&tmp[1]);
		if (res)
			return (res);
		i++;
	}
	return (res);
}

char		**convert_lst(t_env *lst)
{
	char	**tmp;
	char	*var;
	int		i;
	t_env	*temp;

	i = 0;
	tmp = NULL;
	temp = lst;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	if (!(tmp = (char**)malloc(sizeof(char*) * i + 1)))
		return (NULL);
	temp = lst;
	i = 0;
	while (temp)
	{
		var = ft_strjoin(temp->name, "=");
		tmp[i] = ft_strjoin(var, temp->value);
		free(var);
		i++;
		temp = temp->next;
	}
	tmp[i] = 0;
	return (tmp);
}

int			update_vartab(char *name, char *value, t_globenv *envi)
{
	t_env	*tmp;

	tmp = envi->envlst;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->name) == 0 && value)
		{
			ft_strdel(&tmp->value);
			tmp->value = ft_strdup(value);
			freetab(&envi->envtab);
			envi->envtab = convert_lst(envi->envlst);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
