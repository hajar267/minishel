/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:57:16 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/07 11:35:33 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char *herdoc_read(char *h_d, t_cmds *commands, t_link *envp)
{
	h_d = readline("> ");
	if (!h_d)
		return (NULL) ;
	if (ft_strcmp(h_d, commands->next->data[0]) == 0)
		return (NULL) ;
	if (ft_strchr(h_d, '$') != NULL)
	{
		char *tmp = heredoc_expander(h_d, envp);
		h_d = ft_memset(h_d, 0, ft_strlen(h_d));
		h_d = ft_strdup(tmp);
	}
	return (h_d);
}

char *open_herdoc_file(t_cmds *commands, char *file, t_link *envp)
{
	char *path = find_val(envp, "TMPDIR");
	if (!path)
		return (NULL) ;
	file = ft_strjoin(path, "heredoc");
	if (access(file, F_OK) == -1)
	{
		commands->fd_h = open(file, O_RDWR | O_CREAT | O_TRUNC, 777);
		if (commands->fd_h == -1)
		{
			perror("bash: ");
			return (NULL);
		}
	}
	return (file);
}

void	heredoc(t_cmds	*commands, t_link *envp)
{
	char	*file;

	file = NULL;
	while(commands)
	{
		if(ft_strcmp(commands->data[0], "<<") == 0)
		{
			while(true)
			{
				char *h_d = NULL;
				h_d = herdoc_read(h_d, commands, envp);
				if (!h_d)
					break ;
				file = open_herdoc_file(commands, file, envp);
				if (!file)
					break ;
				ft_putstr_fd(h_d, commands->fd_h);
			}
			unlink(file);
		}
		commands = commands->next;
	}
}
