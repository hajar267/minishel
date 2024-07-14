/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:52:03 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/14 02:57:41 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	handle_white_space(t_token *var, t_token **token, char *line, int i)
{
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return ;
	check_after_spaces(var, token, line, i);
}

void	check_after_spaces(t_token *var, t_token **token, char *line, int i)
{
	t_token	*tmp;

	tmp = lst_new(var, ft_strlen(line) + 1);
	to_next_node(token, tmp);
	if (is_character(line[i]))
		store_data_characters(var, token, line, i);
	else if (is_quote(line[i]) == 1)
		store_data_s_quote(var, token, line, i);
	else if (is_quote(line[i]) == 2)
		store_data_d_quote(var, token, line, i);
	else if (is_separator(line[i]))
		store_data_separator(var, token, line, i);
}
