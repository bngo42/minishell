/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 19:46:16 by bngo              #+#    #+#             */
/*   Updated: 2017/03/16 14:09:45 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void        add_env(t_env **lst, t_env *newlink)
{
    t_env *tmp;
    
    tmp = *lst;
    if (!(*lst))
        *lst = newlink;
    while ((*lst)->next)
        *lst = (*lst)->next;
    (*lst)->next = newlink;
    *lst = tmp;
}

void		init_env(t_globenv *envi)
{
	char	*buff;

	buff = NULL;
	envi->cpath = getcwd(buff, 512);
	if ((envi->envtab = (char**)malloc(sizeof(char*) * 7)))
	{
		envi->envtab[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/munki");
		envi->envtab[1] = ft_strdup("HOME=/Users/bngo");
		envi->envtab[2] = ft_strdup("LOGNAME=bngo");
		envi->envtab[3] = ft_strdup("SHLVL=1");
		envi->envtab[4] = ft_strdup("PWD=/Users/bngo");
		envi->envtab[5] = ft_strdup("OLDPWD=/Users/bngo");
		envi->envtab[6] = 0;
	}
	if (buff)
		ft_strdel(&buff);
}

t_env		*init_link(char *name, char *value)
{
	t_env *new;

	if (!(new = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (name)
		ft_strdel(&name);
	if (value)
		ft_strdel(&value);
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
		}
		while (env[++i])
		{
			if ((tmp = ft_strsplit(env[i], '=')))
			{
				new = init_link(tmp[0], tmp[1]);
				add_env(&lst, new);
			}
		}
	}
	return (lst);
}
