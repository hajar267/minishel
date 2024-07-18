/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:41:35 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/18 06:58:48 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	store_data_characters(t_token *var, t_token **token, char *line, int i)
{
	t_token	*last;

	last = ft_lstlast(*token);
	while (line[i] && is_character(line[i]))
	{
	/* if (line[i] == '$')
	{
		last->content[var->j++] = 'x';
		while(line[i] != '$' && ...)
		{	
			last->content[var->j++] = 'x';
			i++;
		}
		we send the line and the start and the end to that function to get the value of $
	}
	else
	*/
		last->content[var->j++] = line[i++];
	}
	last->content[var->j] = '\0';
	if (!line[i])
		return ;
	check_after_character(var, token, line, i);
}

/*
	i found a small problms with $ in char so i thing i will create a int in my struct 
	and i will assigned for each token has a single quotes 1 and double quotes 2
	and 0 for others 
*/
void	check_after_character(t_token *var, t_token **token, char *line, int i)
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
	return ;
}
