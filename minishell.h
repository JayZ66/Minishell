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
# include "get_next_line/get_next_line.h"
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
#include <signal.h>

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
	int		last_exit_status;
} t_minishell;


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
void	shell_level(char **env);

void	execute_pipe(int nb_args, char **cmd_line, char **env);
void	do_pipes(char *cmd, char **env);

char	**lst_to_tab(t_token *token);
void	print_tab(char **cmd_line);
int		lst_size(t_token *token);
void	free_tab(char **tab);

int		manage_file(int nb_args, char **cmd_line, int flag);
char	*check_line_cmd(t_token *token);



// tokenisation
int	tokenize_separator(t_token **token, char *input, int i, char **env);
int	tokenize_arg(t_token **token, char *input, int i);
int	tokenize_double_quote(t_token **token, char *input, int i, char **env);
int	tokenize_simple_quote(t_token **token, char *input, int i);


// Var. env.
char	*get_the_var_of_env(t_token *node);


// Utils
t_token	*init_node(char *content, Token_type type);
t_token	*lst_last(t_token *token);
void	add_back(t_token **token, t_token *new);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strcat(char *dst, const char *src, size_t size);
void	print_lst(t_token *token);
void	print_new_env(char **env);
int		ft_strlen_tab(char **cmd_line);
int		ft_lstsize_content(t_token *token);
void	free_that_lst(t_token **token);
char	**realloc_env(char **env);
size_t	ft_size_env(char **env);
int		ft_strncmp_limiter(const char *s1, const char *s2, size_t n);


// Built_in
void	builtin_exit(char **args);
void	builtin_pwd();
char	**builtin_unset(char **var, char **new_env);
void	builtin_env(char **env);
char	**builtin_export(char **args, char **env);
char	**create_var_env(char **env, char *var);
char	**modify_value_env(char **env, char *var, char *new_value);
char	**modify_or_create_var(char **args, char **env, size_t i, char **new_env);
char	*copy_new_value(char *new_env, char *var, char *new_value);
int		is_var_in_env(char *var, char **env);
void	update_env(char **env, char *var);
void	sort_tab(char **env);
char	**print_env(char **env);
char	**builtin_cd(char **env, char **cmd);
int		is_relative_path(char **cmd);
char	*relative_to_absolute_path(char **cmd);
char	**go_back_home(char **new_env, char **env);
char	**env_with_new_pwd(char **new_env, char **env, char *new_pwd);
char	**get_new_pwd(char **env, char **new_env, char **cmd);
char	**change_pwd_env(char **env, char **new_env, size_t cwd_len, char *cwd);
void  	echo(char *str);
void  	handle_echo_with_n(char **cmd);
char  	*clean_quote(char *str);
char	*handle_quotes(char *cmd);


// Execution
char	**select_path(char **env);
char	*get_path(char *cmd, char **env);
void	exec_cmd_with_fork(char *cmd, char **env, t_minishell *exit_code);
void	child_cmd_only(char **cmd_line, char **env);
void	parent_cmd_only(int pid, t_minishell *exit_code);
void	exec_cmd(char *cmd, char **env);
void	parent_process(int *pfd, char *cmd, char **env, t_minishell *exit_code);
void	child_process(int *pfd, char *cmd, char **env);
void	create_pipes(char *cmd, char **env, t_minishell *exit_code);
void	parent_here_doc(int *pfd, char *cmd, t_minishell *exit_code);
void	child_here_doc(int *pfd, char *cmd);
void	handle_here_doc(char *cmd, t_minishell *exit_code);
void	check_line(t_token **lst, char **env, t_minishell *exit_code);
void 	append_exec_node(t_token **head, char *content, Token_type type);
t_token	*create_command_list();
t_token	*create_command_list2(void);
t_token	*create_command_list3(void);
t_token	*create_command_list4(void);
t_token	*create_command_list5(void);
t_token	*create_command_list6(void);
void 	print_exec_list(t_token *head);
void	display_lst(t_token *line);

// SIGNALS
void 	sigint_handler(int sig);
void	manage_signals();
void	sigquit_handler(int sig);

#endif
