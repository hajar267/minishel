/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:10:11 by istili            #+#    #+#             */
/*   Updated: 2024/07/31 12:17:49 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (!s[i])
		return (1);
	return (0);
}

void	f_exit(char **av)
{
	int	status;

	status = EXIT_SUCCESS;
	if (av[1] == 0)
	{
		write(1, "exit\n", 5);
		ft_malloc_gab(0, 1);
		exit(status);
	}
	if (!is_number(av[1]))
	{
		write(1, "exit\n", 5);
		write(1, "bash: exit: numeric argument required\n", 39);
		ft_malloc_gab(0, 1);
		exit(255);
	}
	if (av[2])
	{
		write(1, "bash: exit: too many arguments\n", 31);
		exit_status(1, 1);
		ft_malloc_gab(0, 1);
		return ;
	}
	write(1, "exit\n", 5);
	ft_malloc_gab(0, 1);
	exit(ft_atoi(av[1]));
}
