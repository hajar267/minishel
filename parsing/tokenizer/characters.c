/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:41:35 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/28 11:57:05 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	store_data_characters(t_token *var, t_token **token, char *line, int i)
{
	t_token	*last;

	last = ft_lstlast(*token);
	while (line[i] && is_character(line[i]))
	{
		if (line[i] == '$')
		{
			i++;
			int j = i;
			while(line[i] && line[i] != '$' && (!is_separator(line[i])) && (!is_space(line[i])) && (is_quote(line[i]) == 0))
				i++;
			char *data = ft_replace(line, j, i - 1);
			int len = ft_strlen(data);
			last->content = (char *)ft_realloc(last->content, var->j + len + 1 + var->len, var->j);
			if (!last->content)
				return (-1);
			int x = 0;
			while(data[x])
				last->content[var->j++] = data[x++];
		}
		else
			last->content[var->j++] = line[i++];
	}
	last->content[var->j] = '\0';
	if (!line[i])
		return (1);
	if (check_after_character(var, token, line, i) == -1)
		return (-1);
	return (1);
}

int	check_after_character(t_token *var, t_token **token, char *line, int i)
{
	t_token	*tmp;

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
	else if (is_separator(line[i]))
	{
		tmp = lst_new(var, ft_strlen(line) + 1);
		to_next_node(token, tmp);
		if (store_data_separator(var, token, line, i) == -1)
			return (-1);
	}
	else if (is_space(line[i]))
	{
		if (handle_white_space(var, token, line, i) == -1)
			return (-1);
	}
	return (1);
}
