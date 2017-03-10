/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:40:06 by bngo              #+#    #+#             */
/*   Updated: 2017/03/10 17:44:48 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_trstr(char *str, int count)
{
	char	*res;
	int		i;
	int		j;

	i = count;
	if (i > ft_strlen(str))
		return (NULL);
	if (!(res = (char*)malloc(sizeof(char) * ((ft_strlen(str) - count) + 1))))
		return (NULL);
	while (str[i])
	{
		res[j++] = str[i];
		i++;
	}
	res[j] = 0;
	return (res);
}
