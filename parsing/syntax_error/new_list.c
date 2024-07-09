/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 03:36:57 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/09 01:13:55 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"

int	ft_len_args(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		i++;
	}
	return (i);
}

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
	t_cmds	*node = malloc(sizeof(t_cmds));
	if (!node)
		return(NULL);
	node->data = malloc(sizeof(char *) * (i + 1));
	if (!node->data)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	store_data(t_cmds	**cmnd, t_token	*token)
{
	t_cmds	*last = last_node(*cmnd);
	int j=0;
	while(token->data[j])
	{
		last->data[j] = ft_strdup(token->data[j]);
		j++;
	}
	last->data[j] = NULL;
}

void	convert_to_new_list(t_token	*token, t_cmds	**cmnd)
{
	t_token	*command = ft_new_list(token);
	t_token	*head = command;
	while(head)
	{
		int len = ft_len_args(head->data);
		t_cmds	*tmp = new_node(len);
		add_node(cmnd, tmp);
		t_cmds	*last = last_node(*cmnd);
		int j=0;
		while(head->data[j])
		{
			last->data[j] = ft_strdup(head->data[j]);
			j++;
		}
		// int len = ft_len_args(head->data);
		// while(j < len && head->data[j])
		// {
		// 	if (head->data[j][ft_strlen(head->data[j]) - 1] == '\0')
    	// 		last->data[j] = ft_strdup(head->data[j]);
    	// 	j++;
		// }
		last->data[j] = NULL;
		head = head->next;
	}
}
