/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 19:46:16 by bngo              #+#    #+#             */
/*   Updated: 2017/03/23 15:38:24 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		add_env(t_env **lst, t_env *newlink)
{
	t_env *tmp;

	tmp = NULL;
	if (!(*lst))
		*lst = newlink;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newlink;
		newlink->prev = tmp;
	}
}

void		init_env(t_globenv *envi)
{
	char	*buff;
	char	*tmp;

	tmp = NULL;
	buff = NULL;
	envi->cpath = getcwd(buff, 512);
	if ((envi->envlst = (t_env*)ft_memalloc(sizeof(t_env))))
	{
		tmp = ft_strdup(":/sbin:/usr/local/bin:/usr/local/munki");
		envi->envlst->name = ft_strdup("PATH");
		envi->envlst->value = ft_strjoin("/usr/bin:/bin:/usr/sbin", tmp);
		ft_strdel(&tmp);
		newenv("HOME=/Users/bngo", envi);
		newenv("LOGNAME=bngo", envi);
		newenv("SHLVL=1", envi);
		newenv("PWD=/Users/bngo", envi);
		newenv("OLDPWD=/Users/bngo", envi);
	}
	ft_strdel(&buff);
}

t_env		*init_link(char *name, char *value)
{
	t_env *new;

	if (!(new = (t_env*)ft_memalloc(sizeof(t_env))))
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_env		*convert_env(char **env)
{
	int		i;
	char	**tmp;
	t_env	*lst;
	t_env	*new;

	lst = NULL;
	if (env)
	{
		i = 0;
		if ((tmp = ft_strsplit(env[i], '=')))
		{
			lst = init_link(tmp[0], tmp[1]);
			freetab(tmp);
		}
		while (env[++i])
		{
			if ((tmp = ft_strsplit(env[i], '=')))
			{
				new = init_link(tmp[0], tmp[1]);
				add_env(&lst, new);
				freetab(tmp);
			}
		}
	}
	return (lst);
}

int			rmlink(t_env **link)
{
	if ((*link)->prev)
		(*link)->prev->next = (*link)->next;
	if ((*link)->next)
		(*link)->next->prev = (*link)->prev;
	ft_strdel(&(*link)->name);
	if ((*link)->value)
		ft_strdel(&(*link)->value);
	free(*link);
	link = NULL;
	return (0);
}
