/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:29:45 by bngo              #+#    #+#             */
/*   Updated: 2017/03/20 12:59:27 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*trijoin(char *s1, char *s2, char *s3)
{
	char *res;
	char *tmp;

	if (s1 && !s2 && !s3)
		res = ft_strdup(s1);
	else if (!s1 && s2 && !s3)
		res = ft_strdup(s2);
	else if (!s1 && !s2 && s3)
		res = ft_strdup(s3);
	else if (s1 && s2 && !s3)
		res = ft_strjoin(s1, s2);
	else if (s1 && !s2 && s3)
		res = ft_strjoin(s1, s3);
	else if (!s1 && s2 && s3)
		res = ft_strjoin(s2, s3);
	else
	{
		tmp = ft_strjoin(s2, s3);
		res = ft_strjoin(s1, tmp);
	}
	if (tmp)
		free(tmp);
	return (res);
}

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
	if (tmp)
		freetab(tmp);
	return (res);
}

char		**convert_lst(t_env *lst)
{
	char	**tmp;
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
		tmp[i++] = trijoin(temp->name, "=", temp->value);
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
		if (ft_strcmp(name, tmp->name) == 0)
		{
			ft_strdel(&tmp->value);
			tmp->value = (value) ? ft_strdup(value) : ft_strnew(0);
			freetab(envi->envtab);
			envi->envtab = convert_lst(envi->envlst);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
