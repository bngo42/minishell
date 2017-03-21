/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpytab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:12:47 by bngo              #+#    #+#             */
/*   Updated: 2017/03/21 18:55:45 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_cpytab(char **tab)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	if (tab)
	{
		while (tab[i])
			i++;
		if (!(tmp = (char**)malloc(sizeof(char*) * i + 1)))
			return (NULL);
		tmp[i] = 0;
		while (--i >= 0)
			tmp[i] = ft_strdup(tab[i]);
	}
	return (tmp);
}
