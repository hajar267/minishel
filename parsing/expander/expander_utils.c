/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 01:18:26 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/08 10:30:45 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// realloc function
#include "../../minishell.h"

void	*ft_realloc(void *ptr, int new_size, int len)
{
	void	*new_ptr;

	new_ptr = NULL;
    if (ptr == NULL)
        return (ft_malloc_gab(new_size, 0));
    new_ptr = ft_malloc_gab(new_size, 0);
    ft_memcpy(new_ptr, ptr, len);
    return (new_ptr);
}

char	*ft_replace(char *line, int start, int end, t_link *envp)
{
	int		len;
	char	*content;
	char	*data;
	int		i;
	char	*e_status;

	i = -1;
	e_status = ft_itoa(exit_status(0, 0));
	len = end - start + 1;
	content = ft_malloc_gab(len + 1, 0);
	data = NULL;
	if (line[start] == '?')
	{
		data = ft_malloc_gab(len + 4, 0);
		while (e_status[++i])
			data[i] = e_status[i];
		start++;
		while (start < end)
			data[i++] = line[start++];
	}
	else
	{
		while(start <= end)
			content[++i] = line[start++];
		content[i] = '\0';
		data = find_val(envp, content);
	}
	if (!data)
		return (ft_strdup(""));
	return (data);
}
