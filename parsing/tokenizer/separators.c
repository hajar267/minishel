/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:53:08 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/08 10:45:59 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	separator(t_token *var, t_token **token, char *line, int i, t_link *envp)
{
	t_token	*last;

	last = ft_lstlast(*token);
	while (line[i] && is_separator(line[i]))
		last->content[var->j++] = line[i++];
	last->content[var->j] = '\0';
	if (!line[i])
	{
		write(2, "my_bash: syntax error near unexpected token\n", 44);
		exit_status(258, 1);
		return (-1);
	}
	if (after_separ(var, token, line, i, envp) == -1)
		return (-1);
	return (1);
}

int	after_separ(t_token *var, t_token **token, char *line, int i, t_link *envp)
{
	t_token	*tmp;

	if (is_space(line[i]))
	{
		if (spaces(var, token, line, i, envp) == -1)
			return (-1);
	}
	else
	{
		tmp = lst_new(var, ft_strlen(line) + 1);
		to_next_node(token, tmp);
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
		else if (is_character(line[i]))
		{
			if (characters(var, token, line, i, envp) == -1)
				return (-1);
		}
	}
	return (1);
}
