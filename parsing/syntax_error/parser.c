/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:41:41 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/09 01:38:26 by hfiqar           ###   ########.fr       */
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

t_token	*ft_lst_new(t_token	*var, int len)
{
	t_token	*command;
	command = malloc(sizeof(t_token));
	if (!command)
		return(NULL);
	command->data = malloc(sizeof(char *) * len + 1);
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
}

// int	get_length(t_token	*token)
// {
// 	int len;

// 	len = 0;
// 	if (!token || !token->content)
// 		return (0);
// 	if (ft_red(token->content) || token->type == PIPE)
// 		return (1);
// 	while(token->content && !ft_red(token->content) && token->type != PIPE)
// 		len++;
// 	return (len);
// }

t_token	*ft_new_list(t_token *token)
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
			tmp = ft_lst_new(head, len);
			to_next_node(&command, tmp);
		}
		ft_store_data(&command, head, j);
	if (!head->next || head->next->type == PIPE || ft_red(head->next->content) \
	|| head->type == PIPE || ft_red(head->content))
		ft_lstlast(command)->data[j++] = NULL;
		// exit(0);
		j++;
		head = head->next;
	}
	return(command);
	// check if all the nodes's data is null terminated
}
// in ft_len_args pass the node t_token and access to its data and count the element into the data
// not safe