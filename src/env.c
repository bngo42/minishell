/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 19:46:16 by bngo              #+#    #+#             */
/*   Updated: 2017/03/08 18:20:31 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void        add_env(t_env **lst, t_env *new)
{
    t_env *tmp;
    
    tmp = *lst;
    if (!(*lst))
        *lst = new;
    while ((*lst)->next)
        *lst = (*lst)->next;
    (*lst)->next = new;
    *lst = tmp;
}

char		**init_env(void)
{
	char	**env;

	if (!(env = (char**)malloc(sizeof(char*) * 7)))
		return (NULL);
	env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/munki");
	env[1] = ft_strdup("HOME=/Users/bngo");
	env[2] = ft_strdup("LOGNAME=bngo");
	env[3] = ft_strdup("SHLVL=1");
	env[4] = ft_strdup("PWD=/Users/bngo");
	env[5] = ft_strdup("OLDPWD=");
	env[6] = 0;
	return (env);
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
		free(name);
	if (value)
		free(value);
	return (new);
}

void		push_link(t_env **lst, t_env *new)
{
	t_env *tmp;

	tmp = *lst;
	if (!(*lst))
		*lst = new;
	else
	{
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = new;
		*lst = tmp;
	}
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
			lst = init_link(tmp[0], tmp[1]);
		while (env[++i])
		{
			if (tmp)
				free(tmp);
			if ((tmp = ft_strsplit(env[i], '=')))
			{
				new = init_link(tmp[0], tmp[1]);
				add_env(&lst, new);
			}
		}
	}
	return (lst);
}
