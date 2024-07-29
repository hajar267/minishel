/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:45:03 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/29 22:44:57 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"

void ft_red_out(t_cmds *command)
{
	command->fd = open(command->next->data[0], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (command->fd == -1)
	{
		printf("failed to open\n");
		exit(EXIT_FAILURE);
	}
	write(command->fd,"here >\n",7);
}

void	ft_append(t_cmds *command)
{
	command->fd = open(command->next->data[0], O_RDWR | O_CREAT | O_APPEND , S_IRUSR | S_IWUSR);
	if (command->fd == -1)
	{
		printf("failed to open\n");
		exit(EXIT_FAILURE);
	}
	write(command->fd,"here >\n",7);
}

void ft_red_in(t_cmds *command)
{
	command->fd = open((const char *)command->next->data[0], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (command->fd == -1)
	{
		printf("failed to open\n");
		exit(EXIT_FAILURE);
	}
	write(command->fd,"here <\n",7);
}

void	ft_open_files(t_cmds	*command)
{
	while(command)
	{
		if (ft_strcmp(command->data[0], ">") == 0)
			ft_red_out(command);
		else if (ft_strcmp(command->data[0], ">>") == 0)
			ft_append(command);
		else if (ft_strncmp(command->data[0], "<", 1) == 0)
			ft_red_in(command);
		command = command->next;
	}
}

// // //if we pass the path when we want to create the file to open function