/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:43:24 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/14 05:44:06 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"

void	ft_error(void)
{
	write(2, "syntax_error !\n", 16);
	return ;
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

bool	ft_red(char *str)
{
	if (token_content_type(str) == REDIRECT_IN || \
	token_content_type(str) == REDIRECT_OUT || \
	token_content_type(str) == APPEND || \
	token_content_type(str) == HEREDOC)
		return (true);
	return (false);
}

t_token_type	token_content_type(char *str)
{
	t_token_type	type;
	int				len;

	type = -1;
	if (is_separator(str[0]))
	{
		len = ft_strlen(str);
		if (ft_strncmp(str, "|", 1) == 0 && len == 1)
			type = PIPE;
		else if (ft_strncmp(str, "<", 1) == 0 && len == 1)
			type = REDIRECT_OUT;
		else if (ft_strncmp(str, ">", 1) == 0 && len == 1)
			type = REDIRECT_IN;
		else if (ft_strncmp(str, ">>", 2) == 0 && len == 2)
			type = APPEND;
		else if (ft_strncmp(str, "<<", 2) == 0 && len == 2)
			type = HEREDOC;
		else
			ft_error();
	}
	return (type);
}

void	check_for_pipe(t_token	*token)
{
	t_token	*head;

	head = token;
	if (token_content_type(head->content) == PIPE)
	{
		write(2, "syntax error !\n", 15);
		return ;
	}
	while (head)
	{
		head->type = token_content_type(head->content);
		if (((head->type == PIPE || ft_red(head->content)) && \
		(head->next == NULL || \
		token_content_type(head->next->content) == PIPE)) || \
		(ft_red(head->content) && ft_red(head->next->content)))
		{
			write(2, "syntax error !\n", 15);
			return ;
		}
		head = head->next;
	}
}
