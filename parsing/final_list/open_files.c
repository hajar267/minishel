/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:45:03 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/08 10:40:19 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_red_out(t_cmds *command)
{
	command->fd = open(command->next->data[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (command->fd == -1)
	{
		perror("my_bash: ");
		exit_status(1, 1);
		return (-1);
	}
	write(command->fd,"red\n",4);
	close (command->fd);
	return (1);
}

int	ft_append(t_cmds *command)
{
	command->fd = open(command->next->data[0], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (command->fd == -1)
	{
		perror("my_bash: ");
		exit_status(1, 1);
		return (-1);
	}
	write(command->fd,"n >\n",4);
	close (command->fd);
	return (1);
}

int ft_red_in(t_cmds *command)
{
	command->fd = open(command->next->data[0], 0644);
	if (command->fd == -1)
	{
		perror("my_bash: ");
		exit_status(1, 1);
		return (-1);
	}
	write(command->fd,"h",1);
	close (command->fd);
	return (1);
}

int	ft_open_files(t_cmds	*command)
{
	while(command)
	{
		if (ft_strcmp(command->data[0], ">") == 0)
		{
			if (ft_red_out(command) == -1)
				return (-1);
		}
		else if (ft_strcmp(command->data[0], ">>") == 0)
		{
			if (ft_append(command) == -1)
				return (-1);
		}
		else if (ft_strncmp(command->data[0], "<", 1) == 0)
		{
			if (ft_red_in(command) == -1)
				return (-1);
		}
		command = command->next;
	}
	return (1);
}
