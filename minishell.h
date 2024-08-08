/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:25:27 by hfiqar            #+#    #+#             */
/*   Updated: 2024/08/08 00:16:13 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "parsing/parsing.h"
#include "execution.h"

void	main_execution(t_cmds *commands, t_link *envp, int flag);
char	*find_val(t_link *envp, char *key);
#endif