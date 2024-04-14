/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:56:42 by marvin            #+#    #+#             */
/*   Updated: 2024/03/01 10:56:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
// # include "get_next_line/get_next_line.h"
// # include "printf/ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <time.h>
#include <errno.h> // perror - strerror
#include <unistd.h> // access - dup2 - execve - fork - pipe - waitpid
#include <sys/wait.h> // Wait
#include <fcntl.h>

// Une structure token
// token cmd;
// token arg;
// token options;

typedef enum
{
    CMD,
	ARG,
	PIPE,
	INPUT,
	OUTPUT,
	APPEND,
	HERE_DOC
} Token_type;

typedef struct	s_token
{
	char			*content;
	Token_type		type;
	struct s_token	*next;
} t_token;

typedef struct s_exec
{
	char	**path;
	char	*cmd;
} t_exec;


typedef struct s_minishell
{
	t_token	*token;
	t_exec	exec;
} t_minishell;

typedef struct s_clean_token
{
	char					*content;
	Token_type				type;
	struct s_clean_token	*next;
} t_clean_token;

// Une structure outils
// path
// envp
// cmd
// args
// here_doc
// pipes
// pid


// MANDATORY PART
char	*read_input();
t_token	*extract_cmd(t_token **token, char *cmd_line, char **env);
t_token	*init_node(char *content, Token_type type);

t_clean_token    *init_clean_node(char *content);

t_token	*lst_last(t_token *token);

t_clean_token	*lst_clean_last(t_clean_token *token);

void	add_back(t_token **token, t_token *new);

void	add_clean_back(t_clean_token **token, t_clean_token *new);

char	*ft_strndup(const char *s, size_t n);
void	shell_level(char **env);

void	execute_pipe(int nb_args, char **cmd_line, char **env);
void	do_pipes(char *cmd, char **env);

char	**lst_to_tab(t_token *token);
void	print_tab(char **cmd_line);
int		lst_size(t_token *token);
void	free_tab(char **tab);

void	exec_cmd(char *cmd, char **env);
char	*select_path(char *cmd, char **env);
char	**get_path(char **env);
int		manage_file(int nb_args, char **cmd_line, int flag);
int		ft_strlen_tab(char **cmd_line);
int		ft_lstsize_content(t_token *token);
char	*check_line_cmd(t_token *token);
char	*ft_strcat(char *dst, const char *src, size_t size);
void	print_lst(t_token *token);

void	print_clean_lst(t_clean_token *token);

void	print_new_env(char **env);


// tokenisation
int	tokenize_separator(t_token **token, char *input, int i, char **env);
int	tokenize_arg(t_token **token, char *input, int i);
int	tokenize_double_quote(t_token **token, char *input, int i, char **env);
int	tokenize_simple_quote(t_token **token, char *input, int i);

t_token    *init_node_separator(Token_type type);

//Clean Node
t_token	*clean_arg(t_token **token);

// t_clean_token	*clean_arg(t_token **token);
t_clean_token	*clean_space(t_clean_token **clean_token);
char	*ft_clean_space(char *content);

//Tokenization
int	tokenize_append(t_token **token, char *input, int i, char **env);
int	tokenize_output(t_token **token, char *input, int i, char **env);
int	tokenize_here_doc(t_token **token, char *input, int i, char **env);
int	tokenize_input(t_token **token, char *input, int i, char **env);
int	tokenize_pipe(t_token **token, int i);


//built-in
void	builtin_or_not_builtin(char *str, char **env);
void	builtin_pwd(char *str);
void	builtin_env(char **env);
void	builtin_exit(char *str);

#endif
