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
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <time.h>
# include <errno.h> // perror - strerror
# include <unistd.h> // access - dup2 - execve - fork - pipe - waitpid
# include <sys/wait.h> // Wait
# include <fcntl.h>
# include <signal.h>

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

typedef struct s_token
{
	char			*content;
	Token_type		type;
	struct s_token	*next;
}	t_token;


typedef struct s_minishell
{
	t_token	*token;
	int		last_exit_status;
}	t_minishell;

typedef struct s_clean_token
{
	char					*content;
	Token_type				type;
	struct s_clean_token	*next;
} t_clean_token;

// MANDATORY PART
char	*read_input(void);
void	shell_level(char **env);

void	execute_pipe(int nb_args, char **cmd_line, char **env);
void	do_pipes(char *cmd, char **env);

// int		manage_file(int nb_args, char **cmd_line, int flag);
// char	*check_line_cmd(t_token *token);

// Var. env.
char	*get_the_var_of_env(t_clean_token *node);

// Utils
// t_token	*init_node(char *content, Token_type type);
// t_token	*lst_last(t_token *token);
// void	add_back(t_token **token, t_token *new);
// char	**lst_to_tab(t_token *token);
void	print_tab(char **cmd_line);
int		lst_size(t_token *token);
void	free_tab(char **tab);

char	*ft_strndup(const char *s, size_t n);
char	*ft_strcat(char *dst, const char *src, size_t size);
// void	print_lst(t_token *token);
void	print_new_env(char **env);
int		ft_strlen_tab(char **cmd_line);
int		ft_lstsize_content(t_token *token);
void	free_that_lst(t_token **token);
char	**realloc_env(char **env);
size_t	ft_size_env(char **env);
int		ft_strncmp_limiter(const char *s1, const char *s2, size_t n);

// Built_in
void	builtin_exit(char **args);
void	builtin_pwd(void);
char	**builtin_unset(char **var, char **new_env);
void	builtin_env(char **env);
char	**builtin_export(char *var_env, char **env);
char	**create_var_env(char **env, char *var);
char	**modify_value_env(char **env, char *var, char *new_value);
char	**modify_or_create(char **args, char **env, size_t i, size_t j);
char	**manage_quote_export(char *input);
int		if_quote(char *var_env);
int		is_something_after_equal(char *str);
char	**clean_spaces(char **args);
char	*copy_new_value(char *new_env, char *var, char *new_value);
int		is_var_in_env(char *var, char **env);
int		is_var_env(const char c);
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
void	builtin_echo(char *str);
void	handle_echo_with_n(char **cmd);
char	*clean_quote(char *str);
char	*handle_quotes(char *cmd);
char	*copy_string_without_char(const char *source, char exclude_char);
int		is_there_something_after_quote(char *str);
char	*copy_str_without_first_quote(char *source);
int		is_space(char c);
char	*check_quotes(char *cmd, int multiple_quotes);
char	*check_multiple_quotes(char *cmd);
char	*check_initial_quote(char *cmd);
char	*removing_one_level_of_quote(char *cmd, char c, size_t i);
int		is_there_multiple_quotes(char *cmd);

// Execution
char	**select_path(char **env);
char	*get_path(char *cmd, char **env);
void	exec_cmd_with_fork(char *cmd, char **env, t_minishell *exit_code);
void	child_cmd_only(char **cmd_line, char **env);
void	parent_cmd_only(int pid, t_minishell *exit_code);
void	exec_cmd(char *cmd, char **env);
void	parent_process(int *pfd, char *cmd, char **env, t_minishell *exit_code);
void	child_process(int *pfd, char *cmd, char **env, int output);
void	create_pipes(char *cmd, char **env, t_minishell *exit_code, int output);
void	parent_here_doc(int *pfd, char *cmd, t_minishell *exit_code);
void	child_here_doc(int *pfd, char *cmd);
void	handle_here_doc(char *cmd, t_minishell *exit_code);
void	manage_here_doc(t_clean_token **current, t_minishell *exit_code, char *content);
void	check_line(t_clean_token **lst, char **env, t_minishell *exit_code);
void	redir_builtin(char *cmd, t_minishell *exit_code, char **env, int out);
void	parent_builtin(int *fd, t_minishell *exit_code);
// void	append_exec_node(t_token **head, char *content, Token_type type);
// t_token	*create_command_list(void);
// t_token	*create_command_list2(void);
// t_token	*create_command_list3(void);
// t_token	*create_command_list4(void);
// t_token	*create_command_list5(void);
// t_token	*create_command_list6(void);
void	print_exec_list(t_token *head);
void	display_lst(t_token *line);
int		manage_output_redirection(char *node_content, int last_file);
int		manage_input_redirection(t_clean_token **current, char *node_content, int first_file);
int		manage_append_redirection(char *node_content, int last_file);
int		manage_redirection_input(t_clean_token **current, t_minishell *exit_code, int first_file);
int		manage_redirection_output(t_clean_token **current, int last_file);
int		manage_cmd_pipe(t_clean_token **current, t_minishell *exit_code, int last_file, char **env);
void	exec_simple_cmd(t_clean_token **current, t_minishell *exit_code, char **env);
void execute_commands_with_pipes(t_clean_token **lst);
void check_line2(t_clean_token **lst, char **env, t_minishell *exit_code);
void exec_cmd_with_pipe2(t_clean_token **current, t_minishell *exit_code, int *pid_array, int index, char **env);
void execute_commands_with_pipes_and_redirections(t_clean_token **lst, char **env, t_minishell *exit_code);

// SIGNAL
void	sigint_handler(int sig);
void	manage_signals(void);
void	sigquit_handler(int sig);

// EXPANSER
int		check_var(t_clean_token *node);
int		handle_quote_errors(char *cmd);
int		builtin_or_not_builtin(char *str, char **env);
int		is_built_in(char *str);
char	*managing_quotes(char *input);
char	*manage_simple_quotes(char *input, int i);
char	*manage_double_quotes(char *input, int i);
char	**split_cmd(char *var_env);



//COPY_LIST
t_clean_token	*copy_lst(t_token *token);

// INIT_CLEAN_NODES
t_clean_token	*init_clean_node(char *content, Token_type type);
t_clean_token	*lst_clean_last(t_clean_token *token);
void			add_clean_back(t_clean_token **token, t_clean_token *new);
void			print_clean_lst(t_clean_token *token);
void			free_that_clean_lst(t_clean_token **token);

// INIT_NODES
t_token			*init_node(char *content, Token_type type);
t_token			*init_node_separator(Token_type type);

// LEXER_PARSER
t_token			*lst_last(t_token *token);
void			add_back(t_token **token, t_token *new);
void			print_lst(t_token *token);
int				string_is_space(char *token);

// TOKENIZER INPUT OUTPUT APPEND HEREDOC
int				tokenize_append(t_token **token, char *input, int i);
int				tokenize_output(t_token **token, char *input, int i);
int				tokenize_here_doc(t_token **token, char *input, int i);
int				tokenize_input(t_token **token, char *input, int i);

// TOKENIZER ARG PIPE
int				tokenize_pipe(t_token **token, int i);
int				tokenize_arg(t_token **token, char *input, int i);

// EXTRACT CMD
t_token			*extract_cmd(t_token **token, char *input);

// CLEAN NODES
void	clean_spaces1(t_token *token);
void			clean_spaces2(t_token *token);
void			clean_chevron(t_token *token);
void			cut_node(t_token *token);
void			manage_node(t_token *token);

// REDIRECTION
void			test_redirection_input(t_clean_token *clean_node);
void			redirection_input(t_clean_token *clean_node);
void			redirection_output(t_clean_token *clean_node);
void			redirection_append(t_clean_token *clean_node);
int				input_in_bloc(t_clean_token *token, int i);

#endif
