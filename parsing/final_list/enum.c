/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:16:28 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/08 10:38:11 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token_type	ft_error(void)
{
	write(2, "my_bash: syntax error near unexpected token\n", 44);
	exit_status(258, 1);
	return (none);
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
			type = Pipe;
		else if (ft_strncmp(str, "<", 1) == 0 && len == 1)
			type = REDIRECT_IN;
		else if (ft_strncmp(str, ">", 1) == 0 && len == 1)
			type = REDIRECT_OUT;
		else if (ft_strncmp(str, ">>", 2) == 0 && len == 2)
			type = APPEND;
		else if (ft_strncmp(str, "<<", 2) == 0 && len == 2)
			type = HEREDOC;
		else
			type = ft_error();
	}
	return (type);
}

bool	ft_si(char *str)
{
	if (token_content_type(str) == REDIRECT_IN || \
	token_content_type(str) == REDIRECT_OUT || \
	token_content_type(str) == APPEND)
		return (1);
	return (0);
}

int	enumeration(t_token *var)
{
	t_token	*head;

	head = var;
	while (head)
	{
		if (token_content_type(head->content) == none)
			return (-1);
		if (token_content_type(head->content) == Pipe)
			head->type = Pipe;
		else if (token_content_type(head->content) == REDIRECT_IN)
			head->type = REDIRECT_IN;
		else if (token_content_type(head->content) == REDIRECT_OUT)
			head->type = REDIRECT_OUT;
		else if (token_content_type(head->content) == APPEND)
			head->type = APPEND;
		else if (token_content_type(head->content) == HEREDOC)
			head->type = HEREDOC;
		else if (!head->prev || token_content_type(head->prev->content) == Pipe)
			head->type = COMMAND;
		else if (ft_si(head->prev->content))
			head->type = file;
		else if (token_content_type(head->prev->content) == HEREDOC)
			head->type = DELIMITER;
		else
			head->type = ARG;
		head = head->next;
	}
	return (1);
}

void	final_enum(t_token	*token, t_token **commands)
{
	t_token	*last;

	last = ft_lstlast(*commands);
	if (token->type == Pipe)
		last->type = Pipe;
	else if (token->type == REDIRECT_IN)
		last->type = REDIRECT_IN;
	else if (token->type == REDIRECT_OUT)
		last->type = REDIRECT_OUT;
	else if (token->type == APPEND)
		last->type = APPEND;
	else if (token->type == HEREDOC)
		last->type = HEREDOC;
	else if (token->type == COMMAND)
		last->type = COMMAND;
	else if (token->type == file)
		last->type = file;
	else if (token->type == DELIMITER)
		last->type = DELIMITER;
}
