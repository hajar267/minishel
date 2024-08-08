/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:27:12 by istili            #+#    #+#             */
/*   Updated: 2024/08/08 01:14:01 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parsing/parsing.h"
# include <term.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# define MALLOC "Error allocating memory\n"
# define OPEN "Error with open\n"
# define FORK "Error with fork\n"
# define PIPE "Error with pipe\n"
# define DUP2 "Error with dup2\n"
# define EXC "Error with execve\n"
# define PATH "Error path not found\n"
# define ARGS "Error invalide args\n"
// # define
// # define 
// # define 
// # define 
// # define 
// # define 
// # define 

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prv;
	void			*data;
}	t_node;

typedef struct s_link
{
	t_node	*head;
	t_node	*tail;
	int		size;
	char	*pwd;
}	t_link;

typedef struct s_env
{
	void	*key;
	void	*val;
}	t_env;

typedef struct s_gab
{
	struct s_gab	*next;
	void			*ptr;
}	t_gab;

typedef struct s_list
{
	t_gab	*head;
}	t_list;

typedef struct s_exc
{
	pid_t	id;
}	t_exc;

void	f_echo(char **av);
void	f_pwd(t_link *linked);
int		f_unset(t_link *linkd, char **av);
int		f_cd(char **path, t_link *envp);
void	f_exit(char **av);
void	f_export(t_link *linkedlist, char **av, int flag_env);
void	f_env(t_link *linkedlist);

char	**ft_split(char *str, char c);
// char	*ft_strchr(char *s, int c);
int		ft_strlen(const char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
// char	*ft_strdup(const char *s1);
char	*ft_strdup_del(void	*dir);
// int		ft_strcmp(char *s1, char *s2);
// char	*ft_strjoin(char *line, char *bufr);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_atoi(const char *str);
int		is_number(char *s);
char	*ft_itoa(int n);

char	*find_home_path(t_link *envp);
int		exit_status(int new_status, int flag);
void	error(char *s);
int		check_arg(char *av);
char	*find_key(char *s, int *flag);
void	updatenv(t_link *link, char *key, char *val);
t_link	*env_linkedlist(char **env);
void	add_node(t_link *node, void *env);
t_link	*make_my_own_env(void);
int		clean_path(char **env, t_cmds *command);
void	handle_siginit(int sig);
void	*ft_malloc_gab(size_t size, int flag);
int		is_alpha_(char c);
int		is_alphnum(char c);
void	pipex(char **env, t_cmds *cmds, int flag);
int		execution(t_link *envp, t_cmds *cmd);
int		fill_cmd(t_cmds *cmds, char **env);
int		count_cmds(t_cmds *cmds);
void	execute_one_cmd(t_cmds *cmd, char **env, pid_t id);

#endif
