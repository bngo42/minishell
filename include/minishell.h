/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 12:30:19 by bngo              #+#    #+#             */
/*   Updated: 2017/03/06 11:52:03 by marvin           ###   ########.fr       */
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

t_env		*convert_tab(char **str);
t_env		*init_env();
#endif
