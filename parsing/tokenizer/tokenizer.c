/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:54:07 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/28 09:45:45 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*ft_strdup(char *s)
{
	size_t		len ;
	char		*str;
	int			i;

	i = 0;
	len = ft_strlen(s);
	str = malloc(len +1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

t_token	*lst_new(t_token *var, int len)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->content = malloc(len + 1);
	if (!node->content)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	var->j = 0;
	return (node);
}

t_token	*ft_lstlast(t_token *data)
{
	if (!data)
		return (NULL);
	while (data->next)
		data = data->next;
	return (data);
}

void	to_next_node(t_token **token, t_token *data)
{
	t_token	*nod;

	if (!(*token))
	{
		(*token) = data;
		return ;
	}
	nod = ft_lstlast((*token));
	nod->next = data;
	data->prev = nod;
	data->next = NULL;
}

t_token	*ft_tokenizer(char *line)
{
	t_token	var;
	t_token	*data;
	t_token	*token;
	int		i;

	var.len = ft_strlen(line);
	data = NULL;
	token = NULL;
	i = 0;
	if (is_space(line[i]))
	{
		if (handle_white_space(&var, &token, line, i) == -1)
			return (NULL);
	}
	else
	{
		data = lst_new(&var, var.len);
		to_next_node(&token, data);
		if (is_quote(line[i]) == 1)
		{
			if (store_data_s_quote(&var, &token, line, i) == -1)
				return (NULL);
		}
		else if (is_quote(line[i]) == 2)
		{
			if (store_data_d_quote(&var, &token, line, i) == -1)
				return (NULL);
		}
		else if (is_separator(line[i]))
		{
			if (store_data_separator(&var, &token, line, i) == -1)
				return (NULL);
		}
		else if (is_character(line[i]))
		{
			if (store_data_characters(&var, &token, line, i) == -1)
				return (NULL);
		}
	}
	return (token);
}
//"hajr"<