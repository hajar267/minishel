/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:19:01 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/22 03:10:24 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"

int	ft_strcmp(const	char	*s1, const	char	*s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char    *ft_strcpy(char *dst, const char *src)
{
        int i = 0;
        while(src[i])
        {
                dst[i] = src[i];
                i++;
        }
        dst[i] = '\0';
        return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i++] = s2[j++];
	}
	str[i] = '\0';
	return (str);
}
