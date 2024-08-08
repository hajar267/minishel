/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:55:59 by istili            #+#    #+#             */
/*   Updated: 2024/08/08 01:39:36 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**link_to_arr(t_link *link)
{
	t_node	*node;
	t_env	*env;
	char	**ret;
	int		i;

	i = 0;
	ret = ft_malloc_gab((link->size + 1) * sizeof(char *), 0);
	node = link->head;
	while (node)
	{
		env = node->data;
		ret[i] = ft_strdup(env->key);
		ret[i] = ft_strjoin(ret[i], "=");
		ret[i] = ft_strjoin(ret[i], env->val);
		i++;
		node = node->next;
	}
	ret[i] = NULL;
	return (ret);
}

// void	red(t_cmds *cmd)
// {
// 	t_cmds	*red;
// 	t_cmds	*tmp;
// 	int		i;

// 	i = 0;
// 	red = cmd;
// 	while (red)
// 	{
// 		tmp = red;
// 		if (!ft_strncmp(red->data[i], ">", 1))
// 	}
// }

int	count_cmds(t_cmds *cmds)
{
	int		count;

	count = 0;
	while (cmds)
	{
		if (!ft_strcmp(*cmds->data, ">") || !ft_strcmp(*cmds->data, "<")
			|| !ft_strcmp(*cmds->data, "<<") || !ft_strcmp(*cmds->data, ">>"))
		{
			cmds = cmds->next;
			if (cmds)
				cmds = cmds->next;
		}
		else if (!ft_strcmp(*cmds->data, "|"))
			cmds = cmds->next;
		else
		{
			cmds = cmds->next;
			count++;
		}
	}
	return (count);
}

void	reset_terminal(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		write(2, "exit\n", 5);
		exit(1);
	}
	term.c_oflag = OPOST | ONLCR;
	term.c_lflag = ICANON | ECHO | ECHOE | ECHOK;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1)
	{
		perror("tcsetattr");
		write(2, "exit\n", 5);
		exit(1);
	}
}

void	setexit(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
		{
			printf("Quit: 3\n");
			reset_terminal();
		}
		else
			printf("\n");
		exit_status(WTERMSIG(status) + 128, 1);
	}
	else
		exit_status(WEXITSTATUS(status), 1);
}

void	execute_one_cmd(t_cmds *cmd, char **env, pid_t id)
{
	int		status;

	status = 0;
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(cmd->data[0], cmd->data, env) == -1)
		{
			write(2, "my_bash: ", 6);
			perror("");
		}
	}
	else
		while (waitpid(-1, &status, 0) != -1)
			;
	setexit(status);
}

int	execution(t_link *envp, t_cmds *cmds)
{
	char	**env;
	int		nb_cmds;
	int		flag;
	t_cmds	*tmp;
	t_cmds	*cur;

	tmp = cmds;
	env = link_to_arr(envp);
	nb_cmds = count_cmds(cmds);
	while (tmp)
	{
		flag = 0;
		cur = tmp;
		while (tmp)
		{
			if (!ft_strcmp(tmp->data[0], "|"))
			{
				flag = 1;
				break ;
			}
			tmp = tmp->next;
		}
		// red(cmds);
		pipex(env, cur, flag);
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}
