/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:26:17 by istili            #+#    #+#             */
/*   Updated: 2024/07/31 13:10:33 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_check(char *av)
{
	int	i;

	if (strlen(av) < 2)
		return (0);
	i = 1;
	while (av && av[i] && av[0] == '-' && av[i] == 'n')
		i++;
	if (!av[i])
		return (1);
	return (0);
}

void	f_echo(char **av)
{
	int	i;
	int	flag;
	int	flag2;

	i = 1;
	flag2 = 0;
	flag = 0;
	while (av[i])
	{
		if (!flag2 && echo_check(av[i]) == 1)
		{
			flag = 1;
			i++;
			continue ;
		}
		flag2 = 1;
		write(1, av[i], ft_strlen(av[i]));
		i++;
		if (av[i])
			write(1, " ", 1);
	}
	if (!flag)
		printf("\n");
}
