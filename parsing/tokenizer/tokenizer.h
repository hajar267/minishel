/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:54:25 by hfiqar            #+#    #+#             */
/*   Updated: 2024/07/17 08:15:35 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_token_type {
	ARG,
	DELIMITER,
	file,
	COMMAND,
	CHAR,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	CHARACTER,
	DOUBLE_QUOTES,
	SINGLE_QUOTES
} t_token_type;

typedef struct s_token {
	t_token_type    type;
	char			*content;
	char			**data;
	struct s_token	*next;
	struct s_token	*prev;
	int				x;
	int				j;
	int				len;
}t_token;

typedef struct s_cmds
{
	char	**data;
	struct s_cmds	*next;
	struct s_cmds	*prev;
	int				j;
	int				fd;
	int				fd_b;
	int				fd_a;
	int				fd_h;
}t_cmds;

//syntax_error_c
void			ft_error(void);
int				ft_strncmp(char *s1, char *s2, int n);
t_token_type	token_content_type(char *str);
void			check_for_pipe(t_token	*token);
void			enumeration(t_token	*var);
bool			ft_si(char	*str);
bool	ft_red(char *str);
int	ft_len(t_token	*token);
t_token	*ft_new_list(t_token *token);
void	check_for_cmd_red_args(t_token	**token);
void	convert_to_new_list(t_token	*token, t_cmds	**cmnd);
// void	check_for_red_args(t_token	**token);
void	ft_open_files(t_cmds	*command);
void convert_it(char *line, t_token **head_ref);
t_token	*ft_tokenizer(char *line);
int	ft_len_args(char **str);

// tokenizer_utils_C
int				is_quote(int c);
bool			is_separator(int c);
bool			is_space(int c);
bool			is_character(int c);
t_token			*lst_new(t_token *var, int len);
int				ft_strlen(const char *str);
void			to_next_node(t_token **token, t_token *data);
t_token			*ft_lstlast(t_token *data);
char			*ft_strdup(char *s);
// handle_quotes_C
void			store_data_s_quote(t_token *var, t_token **token ,char *line, int i);
void			check_after_s_quote(t_token *var, t_token **token ,char *line, int i);
void			store_data_d_quote(t_token *var, t_token **token ,char *line, int i);
void			check_after_d_quote(t_token *var, t_token **token ,char *line, int i);
//handle_characters_C
void			store_data_characters(t_token *var, t_token **token, char *line, int i);
void			check_after_character(t_token *var, t_token **token ,char *line, int i);
//handle_spaces_C
void			handle_white_space(t_token *var, t_token **token, char *line, int i);
void			check_after_spaces(t_token *var, t_token **token, char *line, int i);
//handle_separator_C
void			store_data_separator(t_token *var, t_token **token,char *line, int i);
void			check_after_separator(t_token *var, t_token **token ,char *line, int i);
#endif

// how bash parsing send the data to execution part