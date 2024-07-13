/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:41:41 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/13 01:47:22 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"

int	ft_len(t_token	*token)
{
	int i;

	i = 0;
	while(token)
	{
		token = token->next;
		i++;
	}
	return (i);
}

t_token	*ft_lst_new(int len)
{
	t_token	*command;
	command = malloc(sizeof(t_token));
	if (!command)
		return(NULL);
	command->data = malloc(sizeof(char *) * (len + 1));
	if (!command->data)
		return(NULL);
	command->next = NULL;
	command->prev = NULL;
	return (command);
}

void	ft_store_data(t_token **command, t_token *token, int var)
{
	if (*command == NULL)
        return;
	t_token	*last = ft_lstlast(*command);
	last->data[var] = ft_strdup(token->content);
}

t_token	*ft_new_list(t_token *token) // here
{
	t_token	*command=NULL;
	t_token	*head;
	t_token	*tmp=NULL;
	int j = 0;

	head = token;
	int len = ft_len(head);
	while(head)
	{
		if (!head->prev || ft_red(head->content) || head->type == PIPE || \
		ft_red(head->prev->content) || head->prev->type == PIPE)
		{
			j = 0;
			tmp = ft_lst_new(len);
			to_next_node(&command, tmp);
		}
		ft_store_data(&command, head, j);
	if (head->next == NULL || head->next->type == PIPE || ft_red(head->next->content) \
	|| head->type == PIPE || ft_red(head->content))
	{
		t_token	*lst = ft_lstlast(command);
		lst->data[j+1] = NULL;
	}
	j++;
	head = head->next;
	}
	return(command);
}
