/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:51:26 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/02 22:30:52 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	ft_d_quotes_expdr(int i, t_token **last, t_token *var, char *line)
{
	int		j;
	int		x;
	char	*data;

	if (ft_strcmp((*last)->prev->content, "<<") == 0 && \
	ft_strlen((*last)->prev->content) == 2)
		(*last)->content[var->j++] = line[i++];
	// else if (line[i + 1] == '?')
	// {
		//for exit statu $?
	// }
	else
	{
		i++;
		j = i;
		while(line[i] && line[i] != '$' &&(is_quote(line[i]) == 0) && \
		(!is_separator(line[i])) && (!is_space(line[i])))
			i++;
		data = ft_replace(line, j, i - 1);
		(*last)->content = (char *)ft_realloc((*last)->content, \
		ft_strlen(data) + var->j + 1 + var->len, var->j);
		if (!(*last)->content)
			return (-1);
		x = 0;
		while(data[x])
			(*last)->content[var->j++] = data[x++];
	}
	return (i);
}

int	store_data_d_quote(t_token *var, t_token **token, char *line, int i)
{
	t_token	*last;

	last = ft_lstlast(*token);
	i++;
	while (line[i] && is_quote(line[i]) != 2)
	{
		if (line[i] == '$')
			i = ft_d_quotes_expdr(i, &last, var, line);
		else
			last->content[var->j++] = line[i++];	
			
	}
	last->content[var->j] = '\0';
	if (!line[i])
	{
		write(2, "syntax error_d\n", 16);
		return(-1);
	}
	i++;
	if (check_after_d_quote(var, token, line, i) == -1)
		return (-1);
	return (1);
}

int	helper(t_token *var, t_token **token, char *line, int i)
{
	if ((is_quote(line[i]) == 1))
	{
		if (store_data_s_quote(var, token, line, i) == -1)
			return (-1);
	}
	else if (is_quote(line[i]) == 2)
	{
		if (store_data_d_quote(var, token, line, i) == -1)
			return (-1);
	}
	else if (is_space(line[i]))
	{
		if (handle_white_space(var, token, line, i) == -1)
			return (-1);
	}
	return (1);
}

int	check_after_d_quote(t_token *var, t_token **token, char *line, int i)
{
	t_token	*tmp;
	if (is_quote(line[i]) != 0 || is_space(line[i]))
		{
			if (helper(var, token, line, i) == -1)
				return (-1);
		}
	else if (is_separator(line[i]))
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
