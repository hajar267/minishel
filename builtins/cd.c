/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:41:45 by istili            #+#    #+#             */
/*   Updated: 2024/07/31 13:08:48 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_home(t_link *envp)
{
	char	*path;
	char	*home;

	home = find_home_path(envp);
	if (!home)
	{
		write(2, "bash: cd: HOME not set\n", 23);
		return (1);
	}
	path = ft_strdup(home);
	updatenv(envp, "OLDPWD", ft_strdup(envp->pwd));
	envp->pwd = path;
	updatenv(envp, "PWD", ft_strdup(envp->pwd));
	if (chdir(path) != 0)
	{
		write(2, "bash: cd: ", 10);
		write(2, path, ft_strlen(path));
		perror(" ");
		return (1);
	}
	return (0);
}

static int	cd_something(t_link *envp, char *target)
{
	char	*full_path;

	write(2, "cd: error retrieving current directory:", 39);
	write(2, "getcwd: cannot access parent directories:", 41);
	write(2, "No such file or directory\n", 26);
	updatenv(envp, "OLDPWD", ft_strdup(envp->pwd));
	full_path = ft_strjoin(ft_strdup(envp->pwd), "/");
	full_path = ft_strjoin(full_path, target);
	envp->pwd = full_path;
	updatenv(envp, "PWD", ft_strdup(envp->pwd));
	return (0);
}

int	f_cd(char **target_path, t_link *envp)
{
	char	*target;
	char	*pwd;

	target = target_path[1];
	if (target_path[1] == NULL)
		return (cd_home(envp));
	if (chdir(target) != 0)
	{
		write(2, "bash: cd: ", 10);
		write(2, target, ft_strlen(target));
		perror(" ");
		return (1);
	}
	pwd = ft_strdup_del(getcwd(NULL, 0));
	if (!pwd)
		return (cd_something(envp, target));
	updatenv(envp, "OLDPWD", ft_strdup(envp->pwd));
	envp->pwd = pwd;
	updatenv(envp, "PWD", ft_strdup(envp->pwd));
	return (0);
}
