/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bngo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 12:30:19 by bngo              #+#    #+#             */
/*   Updated: 2017/03/16 14:10:05 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <dirent.h>

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_globenv
{
	char			**envtab;
	t_env			*envlst;
	char			*cpath;
}					t_globenv;

typedef struct		s_built
{
	char			*name;
	int				(*built)(char **str, t_globenv *env);
}					t_built;

/*
 **BUILT.C
*/
int					echo_func(char **str, t_globenv *envi);
int					cd_func(char **str, t_globenv *envi);
int					setenv_func(char **str, t_globenv *envi);
int					unsetenv_func(char **str, t_globenv *envi);
int					env_func(char **str, t_globenv *envi);
int					exit_func(char **str, t_globenv *envi);

/*
 **ENV.C
*/
void				add_env(t_env **lst, t_env *newlink);
void				init_env(t_globenv *envi);
t_env				*init_link(char *name, char *value);
t_env				*convert_env(char **env);

/*
 **EXEC.C
*/
char				**get_cmd_path(t_globenv *envi);
int					exe_cmd(char *path, char **arg, t_globenv *envi);
int					check_cmd(char *path, char **arg, t_globenv *envi);

/*
 **TOOLS.C
*/
int					listlength(t_env *lst);
void				freetab(char **tab);
void				freelst(t_env **lst);
void				update_env(char **env, t_env*lst);

/*
 **MAIN.C
*/
int					get_func(char **str, t_globenv *envi);
void				read_cmd(t_globenv *envi);

/*
 **TOOLS2.C
*/
char				*getlstvalue(char *name, t_globenv *env);
char				*gettabvalue(char *name, t_globenv *env);
int					update_vartab(char*name, char *value, t_globenv *envi);
char				*trijoin(char *s1, char *s2, char *s3);

/*
 **FT_CD.C
*/
int					check_dir(char *path);
char				*pathhome(char *path, t_globenv *envi);
char				*filterpath(char *path);
char				*redirect(char *path);
void				setpath(char *path, char *old, t_globenv *envi);

#endif
