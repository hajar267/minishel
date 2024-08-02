/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:46:41 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/02 22:31:00 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	store_data_s_quote(t_token *var, t_token **token, char *line, int i)
{
	t_token	*last;

	last = ft_lstlast(*token);
	i++;
	while (line[i] && is_quote(line[i]) != 1)
		last->content[var->j++] = line[i++];
	last->content[var->j] = '\0';
	if (!line[i])
	{
		write(2, "syntax error_s\n", 16);
		return (-1);
	}
	else
		i++;
	if (check_after_s_quote(var, token, line, i) == -1)
		return (-1);
	return (1);
}

// int	helper(t_token *var, t_token **token, char *line, int i)
// {
// 	if (store_data_s_quote(var, token, line, i) == -1)
// 		return (-1);
// 	else if (store_data_d_quote(var, token, line, i) == -1)
// 		return (-1);
// 	return (1);
// }

// int	helper_s(t_token *var, t_token **token, char *line, int i)
// {
// 	if (is_quote(line[i]) == 1)
// 	{
// 		if (store_data_s_quote(var, token, line, i) == -1)
// 			return (-1);
// 	}
// 	else if (is_quote(line[i]) == 2)
// 	{
// 		if (store_data_d_quote(var, token, line, i) == -1)
// 			return (-1);
// 	}
// 	else if (is_space(line[i]))
// 	{
// 		if (handle_white_space(var, token, line, i) == -1)
// 			return (-1);
// 	}
// 	return (1);
// }

int	check_after_s_quote(t_token *var, t_token **token, char *line, int i)
{
	t_token	*tmp;

	if (is_quote(line[i] != 0) || is_space(line[i]))
	{
		if (helper(var, token, line, i) == -1)
			return (-1);
	}
	if (is_separator(line[i]))
	{
		tmp = lst_new(var, ft_strlen(line) + 1);
		to_next_node(token, tmp);
		if (store_data_separator(var, token, line, i) == -1)
			return (-1);
	}
	else if (is_character(line[i]))
	{
		if (store_data_characters(var, token, line, i) == -1)
			return (-1);
	}
	return (1);
}
//same for double_quotes
