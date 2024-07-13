/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:45:03 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/13 02:34:48 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"
//function that itterate to each node and open the fd
void	ft_open_files(t_cmds	*command)
{
	while(command)
	{
		if (ft_strncmp(command->data[0], ">>", 2))
		{
			command->fd = open((const char *)command->next->data[0], O_RDWR);
			if (command->fd == -1)
			{
				printf("failed to open\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (ft_strncmp(command->data[0], ">", 1))
		{
			command->fd = open((const char *)command->next->data[0], O_RDWR);
			if (command->fd == -1)
			{
				printf("failed to open\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (ft_strncmp(command->data[0], "<<", 2))
		{
			
		}
		else if (ft_strncmp(command->data[0], "<", 1))
		{
			
		}
		else if (ft_strncmp(command->data[0], "|", 1))
		{
			
		}
		command = command->next;
		// check if there is a red_in or red_out or append or heredoc
		// expl if there is a > i will open a file called the name of the next node->data[0]
	}
}
