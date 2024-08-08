/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:43:24 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/08 10:40:47 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

bool	ft_red(t_token *token)
{
	if (token->type == REDIRECT_IN || \
	token->type == REDIRECT_OUT || \
	token->type == APPEND || \
	token->type == HEREDOC)
		return (true);
	return (false);
}

int	check_for_pipe(t_token	*token)
{
	t_token	*head;

	head = token;
	if (head->type == Pipe)
	{
		write(2, "my_bash: syntax error near unexpected token\n", 44);
		exit_status(258, 1);
		return (-1);
	}
	//head->next == NULL ||
	//ft_red(head->content) &&
	//&& (token_content_type(head->next->content) == Pipe)) || ft_red(head->next->content)
	while (head)
	{
		if ((head->type == Pipe || ft_red(head)) && \
		(head->next != NULL && (ft_red(head->next) || \
		head->next->type == Pipe)))
		{
			write(2, "my_bash: syntax error near unexpected token\n", 44);
			exit_status(258, 1);
			return (-1);
		}
		head = head->next;
	}
	return (1);
}
