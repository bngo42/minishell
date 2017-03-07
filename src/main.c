/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 12:28:11 by bngo              #+#    #+#             */
/*   Updated: 2017/03/07 20:41:20 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			get_func(char **str)
{
	const t_built	fn[6] = {	{"echo", &echo_func},
								{"cd", &cd_func},
								{"setenv", &setenv_func},
								{"unsetenv", &unsetenv_func},
								{"env", &env_func},
								{"exit", &exit_func}
	};
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

void		read_cmd(char **arg, char **envp)
{
	char *line;

	line = NULL;
	get_next_line(0, &line);
	if (line && line[0] != '\0')
	{
		arg = ft_split(line);
		ft_putnbr(get_func(arg));
		if (arg[0] && get_func(arg) && check_cmd(arg[0], arg, envp) == -1)
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(arg[0], 2);
		}
	}
}

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**arg;
	char	**env;
	pid_t	father;
	t_env	*listenv;

	if (!envp)
		env = init_env();
	listenv = convert_env((!envp) ? env : envp);
	while (1)
	{
		ft_putstr("[MINISHELL] ");
		father = fork();
		if (father > 0)
			wait(&argc);
		if (father == 0)
			read_cmd(arg, envp);
	}
	return (0);
}
