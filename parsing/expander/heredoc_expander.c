/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:12:41 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/29 12:47:41 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"

char	*heredoc_expander(char *line)
{
	int		i;
	int		j;
	int		x;
	int		len;
	char	*env;
	char	*data;

	i = 0;
	x = 0;
	data = malloc(ft_strlen(line));
	len = ft_strlen (line);
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			j = i;
			while (line[i] && line[i] != '$' && line[i] != ' ' && (is_quote(line[i]) == 0))
				i++;
			env = ft_replace(line, j, i-1);
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
