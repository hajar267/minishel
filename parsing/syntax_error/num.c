/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:16:28 by hfiqar            #+#    #+#             */
/*   Updated: 2024/06/15 18:26:49 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"

bool	ft_si(char *str)
{
	if (token_content_type(str) == REDIRECT_IN || \
	token_content_type(str) == REDIRECT_OUT || \
	token_content_type(str) == APPEND)
		return (1);
	return (0);
}

void	enumeration(t_token *var)
{
	t_token	*head = var;
	while (head)
	{
		if (token_content_type(head->content) == PIPE)
			head->type = PIPE;
		else if (token_content_type(head->content) == REDIRECT_IN)
			head->type = REDIRECT_IN;
		else if (token_content_type(head->content) == REDIRECT_OUT)
			head->type = REDIRECT_OUT;
		else if (token_content_type(head->content) == APPEND)
			head->type = APPEND;
		else if (token_content_type(head->content) == HEREDOC)
			head->type = HEREDOC;
		else if (!head->prev || token_content_type(head->prev->content) == PIPE)
			head->type = COMMAND;
		else if (ft_si(head->prev->content))
			head->type = file;
		else if (token_content_type(head->prev->content) == HEREDOC)
			head->type = DELIMITER;
		else
			head->type = ARG;
		head = head->next;
	}
}
