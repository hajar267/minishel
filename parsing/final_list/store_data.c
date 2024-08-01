/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 03:36:57 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/01 21:31:13 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"

t_cmds	*last_node(t_cmds *data)
{
	if (!data)
		return (NULL);
	while (data->next)
		data = data->next;
	return (data);
}

void	add_node(t_cmds **token, t_cmds *data)
{
	t_cmds	*nod;

	if (!(*token))
	{
		(*token) = data;
		return ;
	}
	nod = last_node((*token));
	nod->next = data;
	data->prev = nod;
	data->next = NULL;
}

t_cmds	*new_node(int i)
{
	t_cmds	*node;

	node = malloc(sizeof(t_cmds));
	if (!node)
		return (NULL);
	node->data = malloc(sizeof(char *) * (i + 1));
	if (!node->data)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	store_data(t_cmds	**cmd, t_token	*token)
{
	int		j;
	t_cmds	*last;

	j = 0;
	last = last_node(*cmd);
	while (token->data[j])
	{
		last->data[j] = ft_strdup(token->data[j]);
		j++;
	}
	last->data[j] = NULL;
}

void	convert_to_new_list(t_token *token, t_cmds **cmnd)
{
	t_token	*command;
	t_token	*head;
	t_cmds	*tmp;
	int		len;

	command = ft_new_list(token);
	head = command;
	while (head)
	{
		len = ft_len_args(head->data);
		tmp = new_node(len);
		add_node(cmnd, tmp);
		store_data(cmnd, head);
		(*cmnd)->type = head->type;
		head = head->next;
	}
}
