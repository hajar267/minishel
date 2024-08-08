/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:58:51 by istili            #+#    #+#             */
/*   Updated: 2024/07/31 12:17:20 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	ft_strcmp(char *s1, char *s2)
// {
// 	while (*s1 && *s2 && *s1 == *s2)
// 	{
// 		s1++;
// 		s2++;
// 	}
// 	return ((unsigned int)*s1 - (unsigned int)*s2);
// }

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// char	*ft_strchr(char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == (char)c)
// 			return ((char *)&s[i]);
// 		i++;
// 	}
// 	if ((char)c == '\0')
// 		return ((char *)&s[i]);
// 	return (0);
// }

static size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	x;
	size_t	slen;

	x = 0;
	slen = ft_strlen(src);
	if (dstsize != 0)
	{
		while (src[x] && x < (dstsize - 1))
		{
			dst[x] = src[x];
			x++;
		}
		dst[x] = 0;
	}
	return (slen);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		sub = ft_malloc_gab(1, 0);
		sub[0] = '\0';
		return (sub);
	}
	if (len > slen - start)
		len = (slen - start);
	sub = ft_malloc_gab(len + 1, 0);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
