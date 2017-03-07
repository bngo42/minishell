/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 19:46:16 by bngo              #+#    #+#             */
/*   Updated: 2017/03/07 14:29:25 by bngo             ###   ########.fr       */
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

	if (!(env = (char**)malloc(sizeof(char*) * 5)))
		return (NULL);
	env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/munki");
	env[1] = ft_strdup("HOME=/Users/bngo");
	env[2] = ft_strdup("LOGNAME=bngo");
	env[3] = ft_strdup("SHLVL=1");
	env[4] = ft_strdup("PWD=/Users/bngo");
	return (env);
}

t_env		*init_link(char *name, char *value)
{
	t_env *new;

	if (!(new = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void		push_link(t_env *lst, t_env *new)
{
	t_env *tmp;

	tmp = lst;
	if (!lst)
	{
		lst = new;
		return ;
	}
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

t_env		*convert_env(char **env)
{
	int		i;
	char	**tmp;
	t_env	*lst;
	t_env	*new;
	
	if ((tmp = ft_strsplit(env[i], '=')))
		lst = init_link(tmp[0], tmp[1]);
	i = 1;
	while (env[i])
	{
		if (tmp)
			free(tmp);
		if ((tmp = ft_strsplit(env[i], '=')))
		{
			new = init_link(tmp[0], tmp[1]);
			push_link(lst, new);
		}
		i++;
	}
	return (lst);
}





