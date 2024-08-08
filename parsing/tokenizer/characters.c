/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:41:35 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/08 10:24:25 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check(t_token **last)
{
	if ((*last)->prev != NULL && \
	ft_strcmp((*last)->prev->content, "<<") == 0 && \
	ft_strlen((*last)->prev->content) == 2)
		return (1);
	return (-1);
}

int	char_expdr(t_token **last, t_token *var, char *line, int i, t_link *envp)
{
	int		j;
	int		x;
	char	*data;
	int		len;

	if (ft_check(last) == 1)
		(*last)->content[var->j++] = line[i++];
	else
	{
		i++;
		j = i;
		while(line[i] && (is_alphnum(line[i])) == 0)
			i++;
		if (line[j - 1] == '$' && line[j] == '?')
			i++;
		data = ft_replace(line, j, i, envp);
		len = ft_strlen(data) + var->len + var->j + 3;
		(*last)->content = (char *)ft_realloc((*last)->content, len, var->j);
		if (!(*last)->content)
			return (-1);
		x = 0;
		while(data[x])
			(*last)->content[var->j++] = data[x++];
	}
	return (i);
}

int	characters(t_token *var, t_token **token, char *line, int i, t_link *envp)
{
	t_token	*last;

	last = ft_lstlast(*token);
	while (line[i] && is_character(line[i]))
	{
		if (line[i] == '$')
			i = char_expdr(&last, var, line, i, envp);
		else
			last->content[var->j++] = line[i++];
	}
	last->content[var->j] = '\0';
	if (!line[i])
		return (1);
	if (after_char(var, token, line, i, envp) == -1)
		return (-1);
	return (1);
}

int	after_char(t_token *var, t_token **token, char *line, int i, t_link *envp)
{
	t_token	*tmp;

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
	else if (is_separator(line[i]))
	{
		tmp = lst_new(var, ft_strlen(line) + 1);
		to_next_node(token, tmp);
		if (separator(var, token, line, i, envp) == -1)
			return (-1);
	}
	else if (is_space(line[i]))
	{
		if (spaces(var, token, line, i, envp) == -1)
			return (-1);
	}
	return (1);
}
