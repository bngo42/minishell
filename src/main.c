/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 12:28:11 by bngo              #+#    #+#             */
/*   Updated: 2017/02/17 12:31:55 by bngo             ###   ########.fr       */
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

int			check_arg(char *str)
{
	int i;
	int j;
	int state;
	char *path;

	i = ft_strlen(str);
	j = 0;
	state = 0;
	while (i > 0 && str[i - 1] != '/')
		i--;
	if (i <= 0)
		return (state);
	else
	{
		path = ft_strsub(str, 0, i);
		if (ft_strcmp(path, "/bin/") == 0)
			state = 1;
	}
	if (path)
		free(path);
	return (state);
}

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**arg;
	pid_t	father;
	t_env   *env;
	
	env = convert_tab(envp);
	if (env == NULL)
		env = init_env();
    while (env->next)
    {
        ft_putstr(env->name);
        ft_putchar('=');
        ft_putendl(env->value);
        env = env->next;
    }
	while (1)
	{
		ft_putstr("[MINISHELL] ");
		father = fork();
		if (father > 0)
			wait(&argc);
		if (father == 0)
		{
			get_next_line(0, &line);
			if (line && line[0] != '\0')
			{
				arg = ft_split(line);
				if (arg[0] && get_func(arg) && execve(arg[0], arg, envp) == -1)
				{
					ft_putstr_fd("command not found: ", 2);
					ft_putendl_fd(arg[0], 2);
				}
			}
		}
	}
	return (0);
}
