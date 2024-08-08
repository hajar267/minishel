/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:12:41 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/08 10:33:27 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	helper(char *data, char *line, t_values *var)
// {
// 	char	*env;
// 	int		y;

// 	y = 0;
// 	var->i++;
// 	var->j = var->i;
// 	while (line[var->i] && line[var->i] != '$' && line[var->i] != ' ' && \
// 	(is_quote(line[var->i]) == 0))
// 		var->i++;
// 	env = ft_replace(line, var->j, var->i-1);
// 	data = (char *)ft_realloc(data, var->len + var->x + 1 + ft_strlen(env),\
// 	 var->x);
// 	while(env[y])
// 		data[var->x++] = env[y++];
// }

// char	*heredoc_expander(char *line)
// {
// 	char	*data;
// 	t_values	*var;

// 	var = NULL;
// 	var->i = 0;
// 	var->x = 0;
// 	data = malloc(ft_strlen(line));
// 	var->len = ft_strlen (line);
// 	while (line[var->i])
// 	{
// 		if (line[var->i] == '$')
// 			helper(data, line, var);
// 		else
// 			data[var->x++] = line[var->i++];
// 	}
// 	data[var->x] = '\0';
// 	return (data);
// }


char	*heredoc_expander(char *line, t_link *envp)
{
	int		i;
	int		j;
	int		x;
	int		len;
	char	*env;
	char	*data;

	i = 0;
	x = 0;
	data = ft_malloc_gab(ft_strlen(line), 0);
	len = ft_strlen (line);
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			j = i;
			while (line[i] && is_alphnum(line[i]) == 0)
				i++;
			if (line[j - 1] == '$' && line[i] == '?')
				i++;
			env = ft_replace(line, j, i, envp);
			data = (char *)ft_realloc(data, len + x + 1 + ft_strlen(env), x);
			int y=0;
			while(env[y])
			{
				data[x] = env[y];
				x++;
				y++;
			}
		}
		else
		{
			data[x] = line[i];
			x++;
			i++;
		}
	}
	data[x] = '\0';
	return (data);
}
