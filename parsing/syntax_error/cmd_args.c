/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:06:01 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/31 12:12:19 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_for_cmd_red_args(t_token **token)
{
	t_token	*head;
	t_token	*first;
	t_token	*second;

	head = *token;
	while (head)
	{
		first = head;
		second = head->next;
		while (head && head->type != Pipe)
		{
			if (head->type == ARG && head->prev->type == file)
			{
				head->prev->next = head->next;
				head->next = second;
				head->prev = first;
				first->next = head;
				second->prev = head;
			}
			head = head->next;
		}
		if (head)
			head = head->next;
	}
}

// void	check_for_red_args(t_token	**token)
// {
// 	t_token	*head = *token;
// 	while (head)
// 	{
// 		t_token	*first = head;
// 		while (head && head->type != Pipe)
// 		{
			// if (head->type == ARG && first->type != ARG && \
			// first->type != COMMAND)
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
