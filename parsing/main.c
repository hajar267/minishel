/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 02:22:19 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/29 11:22:43 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer/tokenizer.h"

int convert_it(char *line, t_token **head_ref)
{
    t_token *token = ft_tokenizer(line);
	if (token == NULL)
		return (-1);
    t_token *current = NULL;

    while (token)
    {
        current = malloc(sizeof(t_token));
		if (!current)
			return (-1);
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
	return (1);
}

void	read_line(void)
{
	while(true)
	{
		char* line = readline("my_bash-4.5$ ");
		if (!line)
			continue ;
		t_token *tok = NULL;
		t_cmds	*commands =NULL;
		if (convert_it(line, &tok) == -1)
			continue ;
		// we enum just into " " for $
		free(line);
		check_for_pipe(tok);
		enumeration(tok);
		check_for_cmd_red_args(&tok);
		convert_to_new_list(tok, &commands);
		heredoc(commands);
		// ft_open_files(commands);
		while(commands)
		{
			int i = 0;
			while(commands->data[i])
			{
				printf("data : %s  type : %d\n", commands->data[i], tok->type);
				i++;
				if (commands->data[i])
					tok = tok->next;
			}
			tok = tok->next;
			printf("----\n");
			commands = commands ->next;
		}
	while(tok)
	{
		t_token *tmp = tok->next;
		free(tok->content);
		free(tok);
		tok = tmp;
	}
	}
}

int main()
{
	read_line();
}

/*
	ther is a method to implimentate the << the we can call the readline another time 
	in infinite loop and take her > to print it and then we save each line in a char ** or in a file 
	and then we applicate the command before << to the file
*/