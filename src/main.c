/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 12:28:11 by bngo              #+#    #+#             */
/*   Updated: 2017/02/06 14:49:37 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			get_func(char **str)
{
	const t_built	fn[5] = {{"echo", &echo_func}};
	int				i;

	i = 0;
	while (i < 1)
	{
		if (ft_strcmp(fn[i].name, str[0]) == 0)
			return (fn[i].built(str));
		i++;
	}
	return (1);
}

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
		father = fork();
		if (father > 0)
			wait(&i);
		if (father == 0)
		{
			get_next_line(0, &line);
			if (line && line[0] != '\0')
			{
				arg = ft_split(line);
				if (arg[0])
				{
					if (get_func(arg))
					{

						ex = ft_strjoin("/bin/", arg[0]);
						if (execve(ex, arg, NULL) == -1)
						{
							ft_putstr_fd("command not found: ", 2);
							ft_putendl_fd(arg[0], 2);
						}
					}
				}
			}
		}
	}
	return (0);
}
