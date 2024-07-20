/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:51:26 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/20 06:40:33 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	store_data_d_quote(t_token *var, t_token **token, char *line, int i)
{
	t_token	*last;

	last = ft_lstlast(*token);
	i++;
	while (line[i] && is_quote(line[i]) != 2)
	{
		if (line[i] == '$')
		{
			i++;
			int j = i;
			while(line[i] && line[i] != '$' &&(is_quote(line[i]) == 0) && (!is_separator(line[i])) && (!is_space(line[i])))
				i++;
			char *data = ft_replace(line, j, i - 1);
			int len = ft_strlen(data);
			last->content = (char *)ft_realloc(last->content, len + var->len, var->j);
			int x = 0;
			while(data[x])
				last->content[var->j++] = data[x++];
		}
		else
			last->content[var->j++] = line[i++];
	}
	last->content[var->j] = '\0';
	if (!line[i])
	{
		write(2, "syntax error\n", 13);
		return ;
	}
	i++;
	check_after_s_quote(var, token, line, i);
}

void	check_after_d_quote(t_token *var, t_token **token, char *line, int i)
{
	t_token	*tmp;

	if (is_quote(line[i]) == 1)
		store_data_s_quote(var, token, line, i);
	else if (is_quote(line[i]) == 2)
		store_data_d_quote(var, token, line, i);
	else if (is_separator(line[i]))
	{
		tmp = lst_new(var, ft_strlen(line) + 1);
		to_next_node(token, tmp);
		store_data_separator(var, token, line, i);
	}
	else if (is_space(line[i]))
		handle_white_space(var, token, line, i);
	else if (is_character(line[i]))
		store_data_characters(var, token, line, i);
	return ;
}
