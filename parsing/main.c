/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 02:22:19 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/23 04:48:50 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer/tokenizer.h"

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
		// we enum just into " " for $
		free(line);
		check_for_pipe(tok);
		enumeration(tok);
		t_token	*head = tok;
		int fd;
		char *file;
		while(head)
		{
			if(head->type == HEREDOC)
			{
				while(true)
				{
					char *h_d = readline("> ");
					if (!h_d)
						break ;
					if (ft_strcmp(h_d, head->next->content) == 0)
						break ;
					if (ft_strchr(h_d, '$') != NULL)
					{
						char *tmp = heredoc_expander(h_d);
						// free(h_d);
						// h_d = tmp;
						// free(tmp);
						printf("tmp : %s\n", tmp);
						exit(0);
					}
					char *path = getenv("TMPDIR");
					if (!path)
						return;
					file = ft_strjoin(path, "heredoc");
					if (access(file, F_OK) == -1)
					{
						fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 777);
						if (fd == -1)
						{
							printf("error open\n");
							return;
						}
					printf("fd_1 : %d\n", fd);
					}
						int i =0;
					while(h_d[i])
					{
						write(fd, &h_d[i], 1);
						i++;
					}
					write(fd,"\n",1);
					printf("fd_2 : %d\n", fd);
				}
				unlink(file);
				close(fd);
			}
			head = head->next;
		}
		check_for_cmd_red_args(&tok);
		convert_to_new_list(tok, &commands);
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