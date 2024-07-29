/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:41:41 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/14 05:38:15 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"

int	ft_len_args(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_len(t_token *token)
{
	int	i;

	i = 0;
	while (token)
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
		return (NULL);
	command->data = malloc(sizeof(char *) * (len + 1));
	if (!command->data)
		return (NULL);
	command->next = NULL;
	command->prev = NULL;
	return (command);
}

int	ft_store_data(t_token **command, t_token *token, int j, int len)
{
	t_token	*tmp;
	t_token	*last;

	tmp = NULL;
	if (!token->prev || ft_red(token->content) || token->type == PIPE || \
	ft_red(token->prev->content) || token->prev->type == PIPE)
	{
		j = 0;
		tmp = ft_lst_new(len);
		to_next_node(command, tmp);
	}
	last = ft_lstlast(*command);
	last->data[j] = ft_strdup(token->content);
	return (j);
}

t_token	*ft_new_list(t_token *token)
{
	t_token	*command;
	t_token	*head;
	t_token	*lst;
	int		j;
	int		len;

	command = NULL;
	head = token;
	len = ft_len(head);
	j = 0;
	while (head)
	{
		j = ft_store_data(&command, head, j, len);
		if (head->next == NULL || head->next->type == PIPE || \
		ft_red(head->next->content) || head->type == PIPE || \
		ft_red(head->content))
		{
			lst = ft_lstlast(command);
			lst->data[j + 1] = NULL;
		}
		j++;
		head = head->next;
	}
	return (command);
}
