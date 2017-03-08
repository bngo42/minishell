/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 12:28:11 by bngo              #+#    #+#             */
/*   Updated: 2017/03/08 19:29:25 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			get_func(char **str, char **envp, t_env *env)
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
			return (fn[i].built(str, env));
	}
	if (check_cmd(str[0], str, envp))
		return (1);
	return (0);
}

void		read_cmd(char **arg, char **envp)
{
	char *line;
	int		ret;
	t_env	*env;

	line = NULL;
	get_next_line(0, &line);
	if (line && line[0] != '\0')
	{
		arg = ft_split(line);
		env = convert_env(envp);
		if (arg[0] && get_func(arg, envp, env))
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(arg[0], 2);
		}
	}
	ft_strdel(&line);
}

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**arg;
	char	**env;
	t_env	*listenv;

	if (!envp)
		env = init_env();
	listenv = convert_env((!envp) ? env : envp);
	while (1)
	{
		ft_putstr("[MINISHELL] ");
		read_cmd(arg, envp);
	}
	return (0);
}
