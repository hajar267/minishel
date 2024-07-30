/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:26:36 by istili            #+#    #+#             */
/*   Updated: 2024/07/30 12:40:03 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_del(void	*dir)
{
	void		*tmp;
	size_t		size;

	if (!dir)
		return (NULL);
	size = ft_strlen(dir) + 1;
	tmp = ft_malloc_gab(size, 0);
	tmp = ft_memcpy(tmp, dir, size);
	free(dir);
	return (tmp);
}

char	*find_home_path(t_link *envp)
{
	t_node	*head;
	t_env	*env;

	head = envp->head;
	while (head)
	{
		env = head->data;
		if (!ft_strcmp(env->key, "HOME"))
			return (env->val);
		head = head->next;
	}
	return (0);
}

void	updatenv(t_link *link, char *key, char *val)
{
	t_node	*head;
	t_env	*env;

	head = link->head;
	while (head)
	{
		env = head->data;
		if (!ft_strcmp(key, env->key))
			env->val = val;
		head = head->next;
	}
}