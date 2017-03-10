/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trrstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:46:09 by bngo              #+#    #+#             */
/*   Updated: 2017/03/10 17:54:47 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_trrstr(char *str, int count)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = NULL;
	if (str)
	{
		len = ft_strlen(str) - count;
		if (count <= 0 || len <= 0)
			return (ft_strdup(str));
		if (!(res = (char*)malloc(sizeof(char) * len + 1)))
			return (NULL);
		while (i < len)
		{
			res[j++] = res[i];
			i++;
		}
	}
	return (res);
}
