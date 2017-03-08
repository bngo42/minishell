/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 12:30:19 by bngo              #+#    #+#             */
/*   Updated: 2017/03/08 18:33:14 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_built
{
	char			*name;
	int				(*built)(char **str, t_env *env);
}					t_built;

int					echo_func(char **str, t_env *env);
int					cd_func(char **str, t_env *env);
int					setenv_func(char **str, t_env *env);
int					unsetenv_func(char **str, t_env *env);
int					env_func(char **str, t_env *env);
int					exit_func(char **str, t_env *env);

char				**init_env(void);
t_env				*convert_env(char **env);

int					check_cmd(char *path, char **arg, char **env);

int					listlength(t_env *lst);
void				freetab(char ***tab);
void				freelst(t_env **lst);
void				update_env(char **env, t_env*lst);
#endif
