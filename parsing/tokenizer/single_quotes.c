/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:46:41 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/14 02:59:35 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	store_data_s_quote(t_token *var, t_token **token, char *line, int i)
{
	t_token	*last;

	last = ft_lstlast(*token);
	i++;
	while (line[i] && is_quote(line[i]) != 1)
		last->content[var->j++] = line[i++];
	last->content[var->j] = '\0';
	if (!line[i])
	{
		write(2, "syntax error\n", 13);
		return ;
	}
	else
		i++;
	check_after_s_quote(var, token, line, i);
	return ;
}

void	check_after_s_quote(t_token *var, t_token **token, char *line, int i)
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
