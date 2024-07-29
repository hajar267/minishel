/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:57:16 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/29 10:55:32 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer/tokenizer.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void	*ft_memset(void	*b, int c, size_t len)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)b;
	i = 0;
	while (len > i)
	{
		str[i] = c;
		i++;
	}
	return (b);
}

char *herdoc_read(char *h_d, t_cmds *commands)
{
	h_d = readline("> ");
	if (!h_d)
		return (NULL) ;
	if (ft_strcmp(h_d, commands->next->data[0]) == 0)
		return (NULL) ;
	if (ft_strchr(h_d, '$') != NULL)
	{
		char *tmp = heredoc_expander(h_d);
		h_d = ft_memset(h_d, 0, ft_strlen(h_d));
		h_d = ft_strdup(tmp);
		free(tmp);
	}
	return (h_d);
}

char *open_herdoc_file(t_cmds *commands, char *file)
{
	char *path = getenv("TMPDIR");
	if (!path)
		return (NULL) ;
	file = ft_strjoin(path, "heredoc");
	if (access(file, F_OK) == -1)
	{
		commands->fd_h = open(file, O_RDWR | O_CREAT | O_TRUNC, 777);
		if (commands->fd_h == -1)
		{
			printf("error open\n");
			return (NULL);
		}
	}
	return (file);
}

void	heredoc(t_cmds	*commands)
{
	char *file;

	file = NULL;
	while(commands)
	{
		if(ft_strcmp(commands->data[0], "<<") == 0)
		{
			while(true)
			{
				char *h_d = NULL;
				h_d = herdoc_read(h_d, commands);
				if (!h_d)
					break ;
				file = open_herdoc_file(commands, file);
				if (!file)
					break ;
				ft_putstr_fd(h_d, commands->fd_h);
			}
			unlink(file);
		}
		commands = commands->next;
	}
}
