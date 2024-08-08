/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:06:01 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/08 15:26:55 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ft_change(t_token **token)
// {
	
// }

void	check_for_cmd_red_args(t_token **token)
{
	t_token	*head;
	t_token	*first;
	t_token	*second;

	head = *token;
	second = NULL;
	first = NULL;
	while (head)
	{
		while (head && head->type != Pipe)
		{
			if (head->type == file && head->prev)
			{
				second = head;
				first = head->prev;
				// printf("first : %s  second : %s\n", head->prev->content, head->content);
			}
			if (head->type == ARG && head->prev->type == file)
			{
				second->next = head->next;
				if (head->next)
					head->next->prev = second;
				if (first->prev)
				{
					head->prev = first->prev;
					first->prev->next = head;
					head->next = first;
					first->prev = head;
				}
				else {
					head->next = first;
					first->prev = head;
					head->prev = NULL;
					*token = head;
				}
				// printf("head : %s\n", head->content);
				// printf("head->next : %s\n", head->next->content);
				// if (first->prev)
				// 	printf("head->prev : %s\n", head->prev->content);
			}
			head = head->next;
		}
		if (head)
			head = head->next;
	}
	// head = *token;
	// printf("=========\n");
	// int i = 1;
	// while (head) {
	// 	printf("%d ***** %s\n", i, head->content);
	// 	i++;
	// 	head = head->next;
	// }
	// printf("=========\n");
}

// void	check_for_red_args(t_token	**token)
// {
// 	t_token	*head = *token;
// 	while (head)
// 	{
// 		t_token	*first = head;
// 		while (head && head->type != Pipe)
// 		{
// 			if (head->type == ARG && first->type != ARG && \
// 			first->type != COMMAND)
// 			{
// 				head->prev->next = head->next;
// 				head->next->prev = head->prev;
// 				head->prev = NULL;
// 				head->next = first;
// 				first->prev = head;
// 				first = head;
// 				*token = first;
// 			}
// 			head = head->next;
// 		}
// 		if (head)
// 			head = head->next;
// 	}
// }
