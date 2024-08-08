/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:46:41 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/08 10:45:34 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	s_quote(t_token *var, t_token **token, char *line, int i, t_link *envp)
{
	t_token	*last;

	last = ft_lstlast(*token);
	i++;
	while (line[i] && is_quote(line[i]) != 1)
		last->content[var->j++] = line[i++];
	last->content[var->j] = '\0';
	if (!line[i])
	{
		write(2, "unclosed single quotes\n", 23);
		exit_status(1, 1);
		return (-1);
	}
	else
		i++;
	if (after_s_q(var, token, line, i, envp) == -1)
		return (-1);
	return (1);
}

int	after_s_q(t_token *var, t_token **token, char *line, int i, t_link *envp)
{
	t_token	*tmp;

	if (is_quote(line[i]) == 1)
	{
		if (s_quote(var, token, line, i, envp) == -1)
			return (-1);
	}
	else if (is_quote(line[i]) == 2)
	{
		if (d_quote(var, token, line, i, envp) == -1)
			return (-1);
	}
	else if (is_separator(line[i]))
	{
		tmp = lst_new(var, ft_strlen(line) + 1);
		to_next_node(token, tmp);
		if (separator(var, token, line, i, envp) == -1)
			return (-1);
	}
	else if (is_space(line[i]))
	{
		if (spaces(var, token, line, i, envp) == -1)
			return (-1);
	}
	else if (is_character(line[i]))
	{
		if (characters(var, token, line, i, envp) == -1)
			return (-1);
	}
	return (1);
}
