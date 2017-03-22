/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 12:28:11 by bngo              #+#    #+#             */
/*   Updated: 2017/03/22 16:39:39 by bngo             ###   ########.fr       */
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

int			read_cmd(t_globenv *envi)
{
	char	*line;
	int		ret;
	char	**arg;

	line = NULL;
	arg = NULL;
	ret = get_next_line(0, &line);
	if (ret <= 0)
	{
		ft_putendl((ret == 0) ? "exit" : "\n");
		return (-1);
	}
	if (line && line[0] != '\0')
	{
		arg = ft_split(line);
		ft_strdel(&line);
		if (arg[0] && get_func(arg, envi))
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(arg[0], 2);
		}
		freetab(arg);
	}
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	char		*line;
	t_globenv	*envi;

	envi = (t_globenv*)ft_memalloc(sizeof(t_globenv));
	if (!envp[0])
		init_env(envi);
	else
	{
		envi->envlst = convert_env(envp);
		changelvl(envi, 1);
	}
	while (1)
	{
		ft_putstr("[MISHELL] ");
		if (read_cmd(envi) == -1)
			return (-1);
	}
	return (0);
}

int			exit_func(char **str, t_globenv *envi)
{
	int i;
	int e;

	i = 0;
	e = 0;
	while (str[i])
		i++;
	if (i > 2)
		ft_putendl("exit: too many arguments");
	else
	{
		if (str[1])
			e = atoi(str[1]);
		exit((e < 256) ? e : 0);
	}
	return (0);
}
