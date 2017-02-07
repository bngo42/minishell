/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 19:46:16 by bngo              #+#    #+#             */
/*   Updated: 2017/02/07 20:07:22 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env		*init_env_link(char *str)
{
	t_env	*new;
	char	**splitter;

	if (!(new = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	new->next = NULL;
	splitter = ft_strsplit(str, '=');
	if (splitter == NULL)
		return (NULL);
	new->name = splitter[0];
	if (splitter[1])
		new->value = splitter[1];
	if (splitter)
		free(splitter);
	return (new);
}

t_env		*convert_tab(char **str)
{
	int		i;
	char	**splitter;
	t_env	*new_env;
	t_env	*list_env;
	t_env	*tmp;

	i = 0;
	if (!(list_env = init_env_link(str[i])))
		return (NULL);
	i++;
	tmp = list_env;
	while (str[i])
	{
		if (!(new_env = init_env_link(str[i])))
			return (NULL);
		list_env->next = new_env;
		list_env = list_env->next;
		i++;
	}
	list_env = tmp;
	return (list_env);
}
