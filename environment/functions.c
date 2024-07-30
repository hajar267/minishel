/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:58:11 by istili            #+#    #+#             */
/*   Updated: 2024/07/30 12:51:09 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_sign(const char *str, int i)
{
	int	sign;

	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	long	nb;
	long	tmp;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\n' || str[i] == ' ')
		i++;
	sign = check_sign(str, i);
	if (str[i] == '-' || str[i] == '+')
		i++;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = nb * 10 + str[i] - '0';
		if (nb > tmp && sign == 1)
			return (-1);
		if (nb > tmp && sign == -1)
			return (0);
		nb = tmp;
		i++;
	}
	return (nb * sign);
}

int	exit_status(int new_status, int flag)
{
	static int	status;

	status = 0;
	if (flag)
		status = new_status;
	return (status);
}

char	*ft_strjoin(char *line, char *bufr)
{
	char	*s;
	size_t	i;
	size_t	j;

	if (!line || !bufr)
		return (NULL);
	s = (char *)ft_malloc_gab(ft_strlen(line) + ft_strlen(bufr) + 1, 0);
	i = 0;
	while (line != NULL && line[i] != '\0')
	{
		s[i] = line[i];
		i++;
	}
	j = 0;
	while (bufr != 0 && bufr[j] != '\0')
	{
		s[i + j] = bufr[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}
