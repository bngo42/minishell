/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 12:28:11 by bngo              #+#    #+#             */
/*   Updated: 2017/03/09 16:49:28 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			get_func(char **str, t_globenv *envi)
{
	const t_built	fn[6] = {	{"echo", &echo_func},
								{"cd", &cd_func},
								{"setenv", &setenv_func},
								{"unsetenv", &unsetenv_func},
								{"env", &env_func},
								{"exit", &exit_func}};
	int				i;

	i = -1;
	while (++i <= 5)
	{
		if (ft_strcmp(fn[i].name, str[0]) == 0)
			return (fn[i].built(str, envi));
	}
	if (check_cmd(str[0], str, envi))
		return (1);
	return (0);
}

void		read_cmd(char **arg, t_globenv *envi)
{
	char *line;
	int		ret;

	line = NULL;
	get_next_line(0, &line);
	if (line && line[0] != '\0')
	{
		arg = ft_split(line);
		if (arg[0] && get_func(arg, envi))
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(arg[0], 2);
		}
	}
	ft_strdel(&line);
}

void		showtab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		ft_putendl(tab[i++]);
}

int			main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**arg;
	t_globenv	*envi;

	envi = (t_globenv*)malloc(sizeof(t_globenv));
	if (!envp)
		init_env(envi);
	else
		envi->envtab = ft_cpytab(envp);
	envi->envlst = convert_env((!envp) ? envi->envtab : envp);
	while (1)
	{
		ft_putstr("[MINISHELL] ");
		read_cmd(arg, envi);
	}
	return (0);
}
