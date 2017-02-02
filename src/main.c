/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 12:28:11 by bngo              #+#    #+#             */
/*   Updated: 2017/02/02 14:46:52 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			main(int argc, char **argv)
{
	(void)argc;
	char	*line;
	char	**arg;
	char	*ex;
	int		i;
	pid_t	father;

	i = 0;
	while (1)
	{
		ft_putstr("[MINISHELL]");
		get_next_line(0, &line);
		father = fork();
		if (father > 0)
			wait(&i);
		if (father == 0)
		{
			if (line && line[0] != '\0')
			{
				arg = ft_strsplit(line, ' ');
				printf("<%s>\n", arg[0]);
				if (arg[0])
				{
					ex = ft_strjoin("/bin/", arg[0]);
					if (execve(ex, arg, NULL) == -1)
					{
						ft_putstr("command not found: ");
						ft_putendl(arg[0]);
					}
				}
			}
		}
	}
	return (0);
}
