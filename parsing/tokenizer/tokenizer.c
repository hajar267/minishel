/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:54:07 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/09 00:24:07 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <readline/readline.h>
#include <readline/history.h>

char	*ft_strdup(char *s)
{
	size_t		len ;
	char		*str;
	int			i;

	i = 0;
	len = ft_strlen(s);
	str = malloc(len +1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strlen(const char *str)
{
	int i =0;
	while(str[i])
		i++;
	return (i);
}

t_token	*lst_new(t_token *var, int len)
{
	t_token	*node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->content = malloc(len + 1);
	if (!node->content)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	var->j=0;
	return (node);
}

t_token	*ft_lstlast(t_token *data)
{
	if (!data)
		return (NULL);
	while (data->next)
		data = data->next;
	return (data);
}

void	to_next_node(t_token **token, t_token *data)
{
	t_token	*nod;

	if (!(*token))
	{
		(*token) = data;
		return ;
	}
	nod = ft_lstlast((*token));
	nod->next = data;
	data->prev = nod;
	data->next = NULL;
}

t_token	*ft_tokenizer(char *line)
{
	t_token	var;
	t_token *token = NULL;
	t_token *data = NULL;
	int len = ft_strlen(line);
	int i=0;
	if (is_space(line[i]))
		handle_white_space(&var, &token, line, i);
	else
	{
		data = lst_new(&var, len);
		to_next_node(&token, data);
		if (is_quote(line[i]) == 1)
			store_data_s_quote(&var, &token, line, i);
		else if (is_quote(line[i]) == 2)
			store_data_d_quote(&var, &token, line, i);
		else if (is_separator(line[i]))
			store_data_separator(&var, &token, line, i);
		else if (is_character(line[i]))
			store_data_characters(&var, &token, line, i);
	}
	// t_token	*last = ft_lstlast(token);
	// last->next = NULL;
	return (token);
}

void convert_it(char *line, t_token **head_ref)
{
    t_token *token = ft_tokenizer(line);
    t_token *current = NULL;

    while (token)
    {
        current = malloc(sizeof(t_token));
		if (!current)
			return ;
        current->content = ft_strdup(token->content);
        current->next = NULL;
		current->prev = NULL;

        if (*head_ref == NULL)
            *head_ref = current;
        else
        {
            t_token *last = *head_ref;
            while (last->next!= NULL)
                last = last->next;
            last->next = current;
			current->prev = last;
        }
		t_token	*tmp = token->next;
        free(token->content);
        free(token);
		token = tmp;
    }
}
int	get_length(t_token	*token)
{
	int len;

	len = 0;
	if (!token || !token->content)
		return (0);
	if (ft_red(token->content) || token->type == PIPE)
		return (1);
	while(token && !ft_red(token->content) && token->type != PIPE)
	{
		token = token->next;
		len++;
	}
	return (len);
}

void	lk(void)
{
	system ("leaks minicoper");
}
void	read_line(void)
{
	while(true)
	{
		char* line = readline("my_bash-4.5$ ");
		if (!line)
			return ;
		t_token *tok = NULL;
		t_cmds	*commands =NULL;
		convert_it(line, &tok);
		free(line);
		check_for_pipe(tok);
		enumeration(tok);
		check_for_cmd_args(&tok);
		convert_to_new_list(tok, &commands);
		// int len = get_length(tok);
		// printf("len = %d\n", len);
		// while(tok)
		// {
		// 	printf("data : %s\n", tok->content);
		// 	tok = tok ->next;
		// }
	// while(tok)
	// {
	// 	t_token *tmp = tok->next;
	// 	free(tok->content);
	// 	free(tok);
	// 	tok = tmp;
	// }
	}
}

int main()
{
	// atexit(lk);
	read_line();
}
