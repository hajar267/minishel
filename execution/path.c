/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:52:37 by istili            #+#    #+#             */
/*   Updated: 2024/08/08 01:36:45 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**find_path(char **env)
{
	int		i;
	char	**splited_path;

	i = 0;
	splited_path = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			splited_path = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (splited_path);
}

int	clean_path(char **env, t_cmds *command)
{
	int		i;
	char	**path;

	i = 0;
	path = find_path(env);
	if (!path)
	{
		printf("bash: %s: No such file or directory\n", command->data[0]);
		return (1);
	}
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], *(command->data));
		if (!access(path[i], F_OK))
		{
			*(command->data) = path[i];
			return (0);
		}
		i++;
	}
	printf("bash: %s: command not found\n", command->data[0]);
	return (1);
}
