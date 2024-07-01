/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:41:41 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/01 23:50:13 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"

int	ft_len(t_token	*token)
{
	int i;
	t_token	*head;

	i = 0;
	head = token;
	while(head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

t_token	*ft_lst_new(t_token	*var, int len)
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
	var->x = 0;
	return (command);
}

void	ft_store_data(t_token **command, t_token *token, int var)
{
	if (*command == NULL)
        return;
	t_token	*last = ft_lstlast(*command);
	last->data[var] = ft_strdup(token->content);
	var++;
	if (!token->next || ft_red(token->next->content) || token->type == PIPE)
		last->data[var] = NULL;
}

t_token	*ft_new_list(t_token *token)
{
	t_token	*command=NULL;
	t_token	*head;
	t_token	*tmp=NULL;
	int j;

	head = token;
	int len = ft_len(token);
	while(head)
	{
		if (!head->prev || ft_red(head->content) || head->type == PIPE || \
		ft_red(head->prev->content) || head->prev->type == PIPE)
		{
			j = 0;
			tmp = ft_lst_new(head, len);
			to_next_node(&command, tmp);
		}
		ft_store_data(&command, head, j);
		j++;
		head = head->next;
	}
	return(command);
}
