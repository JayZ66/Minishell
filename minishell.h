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
# include "ft_printf/ft_printf.h"
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

typedef enum e_state_machine
{
	reg, quote, dquote
}	t_sm;

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

typedef struct s_clean_token
{
	char					*content;
	Token_type				type;
	struct s_clean_token	*next;
}	t_clean_token;

typedef struct s_final_token
{
	char					*content;
	Token_type				type;
	struct s_final_token	*next;
}	t_final_token;

typedef struct s_minishell
{
	t_token			*token;
	t_clean_token	*clean_token;
	t_final_token	*final_token;
	int				last_exit_status;
	char			**env;
}	t_minishell;

// MANDATORY PART
char			*read_input(t_minishell *minishell);
void			shell_level(t_minishell *minishell);

// void	execute_pipe(int nb_args, char **cmd_line, char **env);
// void	do_pipes(char *cmd, char **env);

// int		manage_file(int nb_args, char **cmd_line, int flag);
// char	*check_line_cmd(t_token *token);

// Var. env.
char			*get_the_var_of_env(t_final_token *node, t_minishell *minishell);

// Utils
void			print_tab(char **cmd_line);
int				lst_size(t_token *token);
void			free_tab(char **tab);

char			*ft_strndup(const char *s, size_t n);
char			*ft_strcat(char *dst, const char *src, size_t size);
// void	print_lst(t_token *token);
void			print_new_env(t_minishell *minishell);
int				ft_strlen_tab(char **cmd_line);
int				ft_lstsize_content(t_token *token);
void			free_that_lst(t_token **token);
char			**realloc_env(char **env);
size_t			ft_size_env(char **env);
int				ft_strncmp_limiter(const char *s1, const char *s2, size_t n);
void			print_export_env(t_minishell *minishell);

// Built_in
void			builtin_exit(char **args, t_minishell *exit_code,
	t_minishell *minishell);
char			**is_char_ok(char **args, t_minishell *minishell);
void			if_not_digit(char *args, size_t i, t_minishell *exit_code);
char			**getting_exit_code(char **args, t_minishell *minishell);
void			builtin_pwd(void);
int				check_pwd_option(char *str);
void			builtin_unset(char **var, t_minishell *minishell);
void			builtin_env(t_minishell *minishell);
void			builtin_export(char **args, t_minishell *minishell);
char			**create_var_env(t_minishell *minishell, char *var);
void 			modify_value_env(char ***env, const char *var, const char *value,
	t_minishell *minishell);
void			modify_or_create(char **args, t_minishell *minishell,
	size_t i, size_t j);
int				identifier_errors(char *args);
int				check_char_unset(char c);
int				check_char_export(char c);
int				identifier_errors_unset(char *args);
int				identifier_errors_export(char *args);
char			*check_value(char *var);
char			**manage_quote_export(char *input);
int				if_quote(char *var_env);
int				is_something_after_equal(char *str);
char			**clean_spaces(char **args);
char 			*copy_new_value(const char *var, const char *new_value,
	t_minishell *minishell);
int				is_var_in_env(char *var, t_minishell *minishell);
int				is_var_env(const char c);
void			update_env(char **env, char *var);
void			sort_tab(char **env);
void			print_env(t_minishell *minishell);
int				is_relative_path(char **cmd);
char			*relative_to_absolute_path(char **cmd, t_minishell *minishell);
void 			env_with_new_var(char ***env, const char *var, const char *value);
void 			change_pwd_env(t_minishell *minishell, const char *cwd,
	const char *old_cwd);
void 			get_new_pwd(t_minishell *minishell, char **cmd);
void 			builtin_cd(t_minishell *minishell, char **cmd);
void 			go_back_home(t_minishell *minishell);
int				check_cd_errors(char **cmd, t_minishell *minishell);
char			*create_new_var(const char *var, const char *value);
char			**alloc_new_env(size_t i, char *new_var, char ***env);
void			builtin_echo(char *str, t_minishell *exit_code);
void			how_many_back_slash(char *cmd);
void			handle_echo_with_n(char **cmd);
int				echo_option(char *cmd);
size_t			count_sign(char **cmd);
char			*clean_quote(char *str);
char			*handle_quotes(char *cmd, t_minishell *minishell);
char			*copy_string_without_char(const char *source,
	char exclude_char);
int				is_there_something_after_quote(char *str);
char			*copy_str_without_first_quote(char *source);
int				is_space(char c);
char			*check_quotes(char *cmd, int multiple_quotes);
char			*check_multiple_quotes(char *cmd);
char			*check_initial_quote(char *cmd);
char			*removing_one_level_of_quote(char *cmd, char c, size_t i);
int				is_there_multiple_quotes(char *cmd);

// Execution
char			**select_path(t_minishell *minishell, char *cmd);
char			*get_path(char *cmd, t_minishell *minishell);
void			exec_cmd_with_fork(char *cmd, t_minishell *minishell,
	t_minishell *exit_code);
void			child_cmd_only(char **cmd_line, t_minishell *minishell, char *cmd);
void			parent_cmd_only(int pid, t_minishell *exit_code);
void			exec_absolute_path(char **cmd_line, char *cmd, t_minishell *minishell);
void			exec_relative_path(char **cmd_line, t_minishell *minishell);
void			exec_cmd(char *cmd, t_minishell *minishell);
void			parent_process(int *pfd, char *cmd, t_minishell *exit_code);
void			child_process(int *pfd, char *cmd, t_minishell *minishell,
	int output);
void			create_pipes(char *cmd, t_minishell *minishell,
	t_minishell *exit_code, int output);
void			parent_here_doc(int *pfd, char *cmd, t_minishell *exit_code);
void			child_here_doc(int *pfd, char *cmd, int alone, t_minishell *exit_code);
void			read_on_terminal(size_t i, char **limiter, t_minishell *exit_code);
void			handle_here_doc(char *cmd, t_minishell *exit_code, int alone);
void			manage_here_doc(t_final_token **current, t_minishell *exit_code,
	char *content, int alone);
void			check_line(t_final_token **lst, t_minishell *minishell,
	t_minishell *exit_code);
void			redir_builtin(char *cmd, t_minishell *exit_code,
	t_minishell *minishell, int out);
void			parent_builtin(int *fd, t_minishell *exit_code);
void			child_builtin(int *fd, int out);
void			print_exec_list(t_token *head);
void			display_lst(t_token *line);
int				manage_output_redirection(char *node_content, int last_file,
	t_minishell *minishell);
int				manage_input_redirection(t_final_token **current, char *node_content,
	int first_file, t_minishell *exit_code);
int				manage_append_redirection(char *node_content, int last_file,
	t_minishell *minishell);
int				manage_redirection_input(t_final_token **current,
	t_minishell *exit_code, int first_file);
int				manage_redirection_output(t_final_token **current, int last_file,
	t_minishell *minishell);
int				manage_cmd_pipe(t_final_token **current, t_minishell *exit_code,
	int last_file, t_minishell *minishell);
void			exec_simple_cmd(t_final_token **current, t_minishell *exit_code,
	t_minishell *minishell);
void 			execute_commands_with_pipes_and_redirections(t_final_token **lst,
	t_minishell *minishell, t_minishell *exit_code);
int				manage_solo_append_redirection(char *node_content, int last_file,
	t_minishell *minishell);
int				manage_solo_output_redirection(char *node_content, int last_file,
	t_minishell *minishell);
int				manage_solo_input_redirection(t_final_token **current, char *node_content,
	int first_file, t_minishell *exit_code);
void			exec_pipe_simple_cmd(t_clean_token **current, t_minishell *exit_code, char **env);
void			exec_cmd_with_pipe(t_final_token **current, t_minishell *exit_code,
	int last_file, t_minishell *minishell);
int				manage_pipe_output(t_final_token **current, t_minishell *minishell,
	t_minishell *exit_code);
int				how_many_output(t_final_token **current);

// SIGNAL
void			sigint_handler(int sig);
void			manage_signals(t_minishell *minishell);
void			sigquit_handler(int sig);

// EXPANSER
int				check_var(t_final_token *node);
int				handle_quote_errors(char *cmd, t_minishell *minishell);
int				builtin_or_not_builtin(char *str, t_minishell *minishell,
	t_minishell *exit_code);
int				is_built_in(char *str);
char			*managing_quotes(char *input, t_minishell *minishell);
char			*manage_simple_quotes(char *input, int i);
char			*manage_double_quotes(char *input, int i);
char			**split_cmd(char *var_env);
int				is_absolute_path(char **cmd);
void			remove_quotes_cmd_line(t_final_token *node, t_minishell *minishell);

//COPY_LIST
t_clean_token	*copy_lst(t_token *token);

// INIT_CLEAN_NODES
t_clean_token	*init_clean_node(char *content, Token_type type);
t_clean_token	*lst_clean_last(t_clean_token *token);
void			add_clean_back(t_clean_token **token, t_clean_token *new);
void			print_clean_lst(t_clean_token *token);
void			free_that_clean_lst(t_clean_token **token);
void    		free_that_final_lst(t_final_token **token);

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
int				tokenize_arg(t_token **token, char *input, int i, t_sm handle_quote);

// EXTRACT CMD
t_token			*extract_cmd(t_token **token, char *input);

// CLEAN NODES
void			clean_spaces1(t_token *token);
void			clean_spaces2(t_token *token);
void			clean_chevron(t_token *token);
void			cut_node(t_token *token);
void			manage_node(t_token *token);

// REDIRECTION
void			test_redirection_input(t_clean_token *clean_node);
int				redirection_input(t_clean_token *clean_node);
void			redirection_output(t_clean_token *clean_node);
void			redirection_append(t_clean_token *clean_node);
int				input_in_bloc(t_clean_token *token, int i);
void			redirection_here_doc(t_clean_token *clean_node, int i);
void			read_here_doc(size_t i, char **limiter);


// INIT FINAL NODE
t_final_token	*final_clean_node(t_clean_token *token);
t_final_token	*init_final_node(char *content, Token_type type);
t_final_token	*lst_final_last(t_final_token	*token);
void			add_final_back(t_final_token **token, t_final_token *new);
void			print_final_lst(t_final_token *token);

// VERIF PIPE CHEVRONS
int				verif_pipe(t_token *token);

char 			*clean_quote(char *input);
// void	echo(char *str);

// VARIABLE D'ENVIRONNEMENT
void			replace_var_of_env(char *content, char *var, int i);
int				len_of_var_of_env(char *content);
void			get_var_of_env(t_final_token *node);

// CHECK DIRECTORY 

int				only_slash(char *content);
void			check_directory(t_token	*node);

// QUOTE
void			set_quotes_state(char *curr_char, int i, t_sm *handle_quote);
char    		*remove_first_level_quote(char *content);
void    		remove_quote(t_final_token *token);
char 			*extract_of_the_var(char *str);

#endif
