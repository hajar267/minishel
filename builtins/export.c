/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:41:30 by istili            #+#    #+#             */
/*   Updated: 2024/08/03 10:43:28 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_value(char *s)
{
	int		i;
	int		j;
	int		k;
	char	*value;

	i = 0;
	while (s[i] && s[i] != '+' && s[i] != '=')
		i++;
	if (!s[i])
		return (NULL);
	if (s[i] == '+')
		i += 2;
	else if (s[i] == '=')
		i++;
	j = i;
	while (s[j])
		j++;
	value = ft_malloc_gab(j - i + 1, 0);
	k = 0;
	while (i < j)
		value[k++] = s[i++];
	value[k] = '\0';
	return (value);
}

static void	replace(t_link *linkedlist, char *key, char *val, int flag)
{
	t_node	*node;
	t_env	*env;

	node = linkedlist->head;
	while (node)
	{
		env = node->data;
		if (!ft_strcmp(env->key, key))
		{
			if (flag == 1)
			{
				env->val = ft_strjoin(env->val, val);
				return ;
			}
			env->val = val;
			return ;
		}
		node = node->next;
	}
	env = ft_malloc_gab(sizeof(t_env), 0);
	env->key = key;
	env->val = val;
	add_node(linkedlist, env);
}

static void	export_printer(t_link *linkedlist, int flag)
{
	t_node	*head;
	t_env	*env;

	head = linkedlist->head;
	while (head)
	{
		env = head->data;
		if (!ft_strcmp(env->key, "_") && flag)
			head = head->next;
		else
		{
			printf("declare -x %s", (char *)env->key);
			if (env->val)
				printf("=%s", (char *)env->val);
			printf("\n");
			head = head->next;
		}
	}
}

void	f_export(t_link *linkedlist, char **av, int flag_env)
{
	char	*key;
	char	*val;
	int		flag;
	int		i;

	key = NULL;
	val = NULL;
	i = 1;
	if (av[i] == NULL)
		export_printer(linkedlist, flag_env);
	while (av[i])
	{
		flag = 0;
		if (check_arg(av[i]) == 1)
		{
			printf("bash: export: `%s': not a valid identifier\n", av[i]);
			i++;
			continue ;
		}
		key = find_key(av[i], &flag);
		val = find_value(av[i]);
		replace(linkedlist, key, val, flag);
		i++;
	}
}
