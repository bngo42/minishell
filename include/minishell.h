/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 12:30:19 by bngo              #+#    #+#             */
/*   Updated: 2017/03/07 19:36:54 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct	s_built
{
	char		*name;
	int			(*built)(char **str);
}				t_built;

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

int			echo_func(char **str);
int			cd_func(char **str);
int			env_func(char **str);
int			setenv_func(char **str);
int			unsetenv_func(char **str);

char		**init_env(void);
t_env		*convert_env(char **env);

int			check_cmd(char *path, char **arg, char **env);
#endif
