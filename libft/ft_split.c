/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:02:26 by bngo              #+#    #+#             */
/*   Updated: 2017/02/02 14:40:24 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	count_words(char *s)
{
	int words;

	while (*s && (*s == ' ' || *s == '\t'))
		++s;
	words = (*s) ? 1 : 0;
	while (*s)
	{
		if ((*s == ' ' || *s == '\t') && s[1] && s[1] != ' ' && s[1] != '\t')
			++words;
		++s;
	}
	return (words);
}

char		**ft_split(char *str)
{
	char	**tab;
	int		i;
	int		j;
	int		start;

	j = 0;
	if (!(tab = (char**)malloc(sizeof(char*) * count_words(str))))
		return (NULL);
	while (str[start])
	{
		i = 0;
		while (str[start] == ' ' || str[start] == '\t')
			start++;
		while (str[start + i] != ' ' && str[start + i] != '\t')
			i++;
		if (i > 0)
		{
			tab[j] = ft_strsub(str, start, i);
			j++;
		}
		start += i;
	}
	return (tab);
}
