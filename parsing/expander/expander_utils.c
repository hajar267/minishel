/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 01:18:26 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/29 12:56:24 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// realloc function
#include "../tokenizer/tokenizer.h"
#include<string.h>

void	*ft_memcpy(void	*dst, const	void *src, size_t n )
{
	unsigned char	*str;
	unsigned char	*str1;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	str = (unsigned char *)dst;
	str1 = (unsigned char *)src;
	i = 0;
	while (n > i)
	{
		str[i] = str1[i];
		i++;
	}
	return ((void *)str);
}

void *ft_realloc(void *ptr, int new_size, int len) // i  can add a 3eme arg to realloc  --> the len of data --> ptr
{
    if (ptr == NULL)
        return (malloc(new_size));
    void *new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return (NULL);
	// printf("size : %d\n", new_size);
    ft_memcpy(new_ptr, ptr, len);
    free(ptr);
    return (new_ptr);
}

//function that get the origin value of $ and return it
char *ft_replace(char *line, int start, int end)
{
	int len = end - start + 1;
	char *content = malloc(len + 1);
	if (!content)
		return(NULL);
	int i = 0;
	while(start <= end)
		content[i++] = line[start++];
	content[i] = '\0';
	// printf("content : %s\n", content);
	char *data = getenv(content);
	if (!data)
		return (ft_strdup(""));
	free (content);
	return (data);
}
