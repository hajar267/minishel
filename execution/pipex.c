/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:11:28 by istili            #+#    #+#             */
/*   Updated: 2024/08/08 09:05:26 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child(char **env, int fd[2], t_cmds *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd[0]);
	// if (dup2(cmd->fd, STDIN_FILENO) == -1)
	// 	error(DUP2);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error(DUP2);
	// close(cmd->fd);
	close(fd[1]);
	if (execve(cmd->data[0], cmd->data, env) == -1)
		perror("bash: ");
}

void	parent(int fd[2])
{
	close(fd[1]);
	// waitpid(-1, NULL, WUNTRACED);
	// if (dup2(cmd->fd, STDOUT_FILENO) == -1)
	// 	error(DUP2);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error(DUP2);
	// close(cmd->fd);
	close(fd[0]);
	// if (execve(cmd->data[0], cmd->data, env) == -1)
	// 	error(EXC);
}

int	fill_cmd(t_cmds *cmds, char **env)
{
	if (cmds->data[0][0] != '/')
	{
		if (clean_path(env, cmds) == 1)
		{
			// Command not found!!
			printf("bash: %s: command not found", cmds->data[0]);
			exit_status(127, 1);
			return (1);
		}
	}
	else if (access(cmds->data[0], F_OK))
	{
		perror("my_bash: ");
		exit_status(127, 1);
		return (1);
	}
	return (0);
}

void	pipex(char **env, t_cmds *cmds, int flag)
{
	int		fd[2];
	pid_t	id;

	if (fill_cmd(cmds, env) == 1)
		return ;
	if (flag)
	{
		if (pipe(fd) == -1)
			error(PIPE);
	}
	id = fork();
	if (id == -1)
		error(FORK);
	if (flag)
	{
		if (id == 0)
			child(env, fd, cmds);
		else if (id != 0)
			parent(fd);
	}
	else
		execute_one_cmd(cmds, env, id);
}
