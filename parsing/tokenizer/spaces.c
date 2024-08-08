/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:52:03 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/05 09:36:51 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	spaces(t_token *var, t_token **token, char *line, int i, t_link *envp)
{
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (1);
	if (after_space(var, token, line, i, envp) == -1)
		return (-1);
	return (1);
}

int	after_space(t_token *var, t_token **token, char *line, int i, t_link *envp)
{
	t_token	*tmp;

	tmp = lst_new(var, ft_strlen(line) + 1);
	to_next_node(token, tmp);
	if (is_character(line[i]))
	{
		if (characters(var, token, line, i, envp) == -1)
			return (-1);
	}
	else if (is_quote(line[i]) == 1)
	{
		if (s_quote(var, token, line, i, envp) == -1)
			return (-1);
	}
	else if (is_quote(line[i]) == 2)
	{
		if(d_quote(var, token, line, i, envp) == -1)
			return (-1);
	}
	else if (is_separator(line[i]))
	{
		if(separator(var, token, line, i, envp) == -1)
			return (-1);
	}
	return (1);
}
