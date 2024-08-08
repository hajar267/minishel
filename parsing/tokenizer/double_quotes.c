/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:51:26 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/08 10:43:54 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	d_q_expdr(int i, t_token **last, t_token *var, char *line, t_link *envp)
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

int	d_quote(t_token *var, t_token **token, char *line, int i, t_link *envp)
{
	t_token	*last;

	last = ft_lstlast(*token);
	i++;
	while (line[i] && is_quote(line[i]) != 2)
	{
		if (line[i] == '$')
			i = d_q_expdr(i, &last, var, line, envp);
		else
			last->content[var->j++] = line[i++];
	}
	last->content[var->j] = '\0';
	if (!line[i])
	{
		write(2, "unclosed double qoutes\n", 24);
		exit_status(1, 1);
		return (-1);
	}
	i++;
	if (after_d_q(var, token, line, i, envp) == -1)
		return (-1);
	return (1);
}

int	after_d_q(t_token *var, t_token **token, char *line, int i, t_link *envp)
{
	t_token	*tmp;

	if ((is_quote(line[i]) == 1))
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
	else if (is_character(line[i]))
	{
		if (characters(var, token, line, i, envp) == -1)
			return (-1);
	}
	return (1);
}
