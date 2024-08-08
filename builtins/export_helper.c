/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:35:57 by istili            #+#    #+#             */
/*   Updated: 2024/08/03 02:28:30 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alpha_(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_')
		return (0);
	return (-1);
}

int	is_alphnum(char c)
{
	if (is_alpha_(c) != -1 || (c >= '0' && c <= '9'))
		return (0);
	return (-1);
}

static int	len(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '+' && s[i] != '=')
		i++;
	return (i);
}

int	check_arg(char *av)
{
	int		i;

	i = 0;
	if (is_alpha_(av[0]) == -1)
		return (1);
	while (av[i] && av[i] != '+' && av[i] != '=')
	{
		if (is_alphnum(av[i]) == -1)
			return (1);
		i++;
	}
	if ((av[i] == '+' && av[i + 1] == '=') || av[i] == '=' || !av[i])
		return (0);
	return (1);
}

char	*find_key(char *s, int *flag)
{
	int		i;
	int		j;
	char	*key;

	i = len(s);
	if (s[i] == '+')
		*flag = 1;
	key = ft_malloc_gab(i + 1, 0);
	j = -1;
	while (++j < i)
		key[j] = s[j];
	key[j] = '\0';
	return (key);
}
