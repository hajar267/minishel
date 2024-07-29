/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:53:08 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/28 09:55:15 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	store_data_separator(t_token *var, t_token **token, char *line, int i)
{
	t_token	*last;

	last = ft_lstlast(*token);
	while (line[i] && is_separator(line[i]))
		last->content[var->j++] = line[i++];
	last->content[var->j] = '\0';
	if (!line[i])
	{
		write(2, "syntax error!\n", 14);
		return (-1);
	}
	if (check_after_separator(var, token, line, i) == -1)
		return (-1);
	return (1);
}

int	check_after_separator(t_token *var, t_token **token, char *line, int i)
{
	t_token	*tmp;

	if (is_space(line[i]))
	{
		if (handle_white_space(var, token, line, i) == -1)
			return (-1);
	}
	else
	{
		tmp = lst_new(var, ft_strlen(line) + 1);
		to_next_node(token, tmp);
		if (is_quote(line[i]) == 1)
		{
			if (store_data_s_quote(var, token, line, i) == -1)
				return (-1);
		}
		else if (is_quote(line[i]) == 2)
		{
			if (store_data_d_quote(var, token, line, i) == -1)
				return (-1);
		}
		else if (is_character(line[i]))
		{
			if (store_data_characters(var, token, line, i) == -1)
				return (-1);
		}
	}
	return (1);
}
