/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:45:03 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/14 01:48:27 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"

void	ft_open_files(t_cmds	*command)
{
	while(command)
	{
		if (ft_strncmp(command->data[0], ">>", 2) == 0)
		{
			command->fd = open((const char *)command->next->data[0], O_RDWR | O_CREAT);
			printf("here\n");
			if (command->fd == -1)
			{
				printf("failed to open\n");
				exit(EXIT_FAILURE);
			}
			write(command->fd,"here >>\n",8);
		}
		else if (ft_strncmp(command->data[0], ">", 1) == 0)
		{
			command->fd = open((const char *)command->next->data[0], O_RDWR | O_CREAT);
			if (command->fd == -1)
			{
				printf("failed to open\n");
				exit(EXIT_FAILURE);
			}
			write(command->fd,"here >\n",7);
		}
		else if (ft_strncmp(command->data[0], "<<", 2) == 0)
		{
			command->fd_h = open("heredoc", O_RDWR | O_CREAT);
			if (command->fd_h == -1)
			{
				printf("failed to open\n");
				exit(EXIT_FAILURE);
			}
			write(command->fd,"here <<\n",8);
		}
		else if (ft_strncmp(command->data[0], "<", 1) == 0)
		{
			command->fd = open((const char *)command->next->data[0], O_RDWR | O_CREAT);
			if (command->fd == -1)
			{
				printf("failed to open\n");
				exit(EXIT_FAILURE);
			}
			write(command->fd,"here <\n",7);
		}
		else if (ft_strncmp(command->data[0], "|", 1) == 0)
		{
			command->fd_a = open("after", O_RDWR | O_CREAT, 777);
			command->fd_b = open("before", O_RDWR | O_CREAT, 777);
			if (command->fd_a == -1)
			{
				perror("Failed to open 'after'");
				exit(EXIT_FAILURE);
			}
			if (command->fd_b == -1)
			{
				perror("Failed to open 'before'");
				exit(EXIT_FAILURE);
			}
			write(command->fd_b,"before\n",7);
			write(command->fd_a,"after\n",6);
			close(command->fd_b);
			close(command->fd_a);
		}
		command = command->next;
	}
}

//if we pass the path when we want to create the file to open function