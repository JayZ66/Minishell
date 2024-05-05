/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:19:26 by marvin            #+#    #+#             */
/*   Updated: 2024/05/05 16:19:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int count_commands(Node *head) {
//     int count = 0;
//     Node *current = head;
//     while (current != NULL) {
//         count++;
//         current = current->next;
//     }
//     return count;
// }

// char **list_to_array(Node *head) {
//     int num_commands = count_commands(head);
//     char **commands = malloc((num_commands + 1) * sizeof(char *)); // +1 pour le NULL à la fin
//     if (commands == NULL) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }

//     Node *current = head;
//     int i = 0;
//     while (current != NULL) {
//         commands[i] = current->command;
//         current = current->next;
//         i++;
//     }
//     commands[num_commands] = NULL; // Marquer la fin du tableau avec NULL
//     return commands;
// }

// void execute_cmd_with_pipe(t_token **current, t_minishell *exit_code, char **env) 
// {
//     int fd[2];
//     pid_t pid;

//     if (pipe(fd) == -1) 
// 	{
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     pid = fork();
//     if (pid == -1) 
// 	{
//         perror("fork");
//         exit(EXIT_FAILURE);
//     } 
// 	else if (pid == 0) 
// 	{ // Processus enfant
//         close(fd[0]); // Ferme l'extrémité de lecture du pipe
//         dup2(fd[1], STDOUT_FILENO); // Redirige la sortie standard vers le pipe
//         close(fd[1]); // Ferme l'extrémité de l'écriture du pipe

//         // Exécute la commande
//         exec_simple_cmd(current, exit_code, env);
//     } 
// 	else 
// 	{ // Processus parent
//         close(fd[1]); // Ferme l'extrémité d'écriture du pipe
//         dup2(fd[0], STDIN_FILENO); // Redirige l'entrée standard vers le pipe
//         close(fd[0]); // Ferme l'extrémité de lecture du pipe

//         // Continue à exécuter les commandes suivantes avec des pipes si elles existent
//         while ((*current)->next != NULL && (*current)->next->type == PIPE) 
// 		{
//             *current = (*current)->next; // Passer à la commande suivante
//             execute_cmd_with_pipe(&((*current)->next), exit_code, env);
//         }
//     }
// }

// void check_line(t_token **lst, char **env, t_minishell *exit_code) 
// {
//     int first_file;
//     int last_file;
//     int saved_stdin;
//     int saved_stdout;
//     t_token *current;

//     current = *lst;
//     saved_stdin = dup(STDIN_FILENO);
//     saved_stdout = dup(STDOUT_FILENO);
//     while (current) 
// 	{
//         first_file = 0;
//         last_file = 0;
//         first_file = manage_redirection_input(&current, exit_code, first_file);
//         last_file = manage_redirection_output(&current, last_file);
//         if (current->type == CMD && (current->next != NULL && current->next->type == PIPE)) 
// 		{
//             execute_cmd_with_pipe(&current, exit_code, env);
//         } 
// 		else if (current->type == CMD) 
// 		{
//             exec_simple_cmd(&current, exit_code, env);
//             dup2(saved_stdin, STDIN_FILENO);
//             dup2(saved_stdout, STDOUT_FILENO);
//         }
//         current = current->next;
//         dup2(saved_stdout, STDOUT_FILENO);
//     }
// }


// void execute_commands_with_pipes(t_token **lst) 
// {
//     int pipefd[2];
//     int fd_in = STDIN_FILENO;
//     pid_t pid;
// 	t_token	*commands;

// 	commands = *lst;
//     while (commands != NULL) 
// 	{
//         // Create a pipe
//         if (pipe(pipefd) == -1) 
// 		{
//             perror("pipe");
//             exit(EXIT_FAILURE);
//         }

//         // Fork a child process
//         if ((pid = fork()) == -1) 
// 		{
//             perror("fork");
//             exit(EXIT_FAILURE);
//         } 
// 		else if (pid == 0) 
// 		{ 
//             // Close the read end of the pipe
//             close(pipefd[0]);
//             // Redirect input from the previous command
//             dup2(fd_in, STDIN_FILENO);
//             close(fd_in);

//             // Redirect output to the pipe
//             if (commands->next != NULL) 
//                 dup2(pipefd[1], STDOUT_FILENO);
// 			else 
//                 // Last command in the pipeline, output to stdout
//                 close(pipefd[1]);

//             // Execute the command
//             execlp(commands->content, commands->content, NULL);
//             // perror("execlp");
//             // exit(EXIT_FAILURE);
//         } 
// 		else 
// 		{
//             // Close the write end of the pipe
//             close(pipefd[1]);
//             // Save the read end of the pipe for the next command
//             fd_in = pipefd[0];
//             // Move to the next command
//             commands = commands->next;
//         }
//     }
//     // Wait for all child processes to finish
//     while (wait(NULL) > 0);
// }


void exec_cmd_with_pipe2(t_token **current, t_minishell *exit_code, int *pid_array, int index, char **env) 
{
    int fd[2];
    if (pipe(fd) == -1) 
	{
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid == -1) 
	{
        perror("fork");
        exit(EXIT_FAILURE);
    } 
	else if (pid == 0) 
	{ // Processus enfant
        close(fd[0]); // Fermer l'extrémité de lecture du pipe
        dup2(fd[1], STDOUT_FILENO); // Rediriger la sortie standard vers le pipe
        close(fd[1]); // Fermer l'extrémité de l'écriture du pipe

        // Exécuter la commande
        exec_simple_cmd(current, exit_code, env);
    } 
	else 
	{ // Processus parent
        close(fd[1]); // Fermer l'extrémité d'écriture du pipe
        dup2(fd[0], STDIN_FILENO); // Rediriger l'entrée standard vers le pipe
        close(fd[0]); // Fermer l'extrémité de lecture du pipe

        // Stocker le PID du processus enfant dans le tableau
        pid_array[index] = pid;
    }
}


// void check_line2(t_token **lst, char **env, t_minishell *exit_code) 
// {
//     int saved_stdin = dup(STDIN_FILENO);
//     int saved_stdout = dup(STDOUT_FILENO);
//     t_token *current = *lst;
//     int pid_array[1024]; // Tableau pour stocker les PIDs des processus enfants
//     int index = 0; // Index pour parcourir le tableau

//     // Création des processus enfants pour chaque commande avec un pipe
//     while (current) 
// 	{
// 		// int first_file = 0;
//         // int last_file = 0;
//         // first_file = manage_redirection_input(&current, exit_code, first_file);
//         // last_file = manage_redirection_output(&current, last_file);
//         if (current->type == CMD && (current->next != NULL && current->next->type == PIPE)) 
// 		{
//             exec_cmd_with_pipe2(&current, exit_code, pid_array, index, env);
//             index++;
//         } 
// 		else if (current->type == CMD) 
// 		{
//             exec_simple_cmd(&current, exit_code, env);
// 			dup2(saved_stdin, STDIN_FILENO);
//         }
// 		// dup2(saved_stdin, STDIN_FILENO);
//         // dup2(saved_stdout, STDOUT_FILENO);
//         current = current->next;
//     }

//     // Attendre la fin de tous les processus enfants
//     for (int i = 0; i < index; i++) {
//         waitpid(pid_array[i], NULL, 0);
//     }

//     // Restaurer les descripteurs de fichier d'entrée et de sortie standard
//     dup2(saved_stdin, STDIN_FILENO);
//     dup2(saved_stdout, STDOUT_FILENO);
// }

// void check_line2(t_token **lst, char **env, t_minishell *exit_code) 
// {
//     // Sauvegarder les descripteurs de fichier d'entrée et de sortie standard
//     int saved_stdin = dup(STDIN_FILENO);
//     int saved_stdout = dup(STDOUT_FILENO);
// 	int	first_file;
// 	int	last_file;
    
//     // Obtenez le premier élément de la liste chaînée
//     t_token *current = *lst;
    
//     // Tableau pour stocker les PIDs des processus enfants
//     int pid_array[1024];
    
//     // Index pour parcourir le tableau
//     int index = 0;
//     while (current) 
//     {
// 		first_file = 0;
//         last_file = 0;
//         first_file = manage_redirection_input(&current, exit_code, first_file);
//         last_file = manage_redirection_output(&current, last_file);
//         // Exécuter la commande avec un pipe s'il y a un pipe
//         if (current->type == CMD && (current->next != NULL && current->next->type == PIPE)) 
//         {
//             exec_cmd_with_pipe2(&current, exit_code, pid_array, index, env);
//             index++;
//         } 
//         else if (current->type == CMD) 
//             exec_simple_cmd(&current, exit_code, env);
        
//         // Passer au prochain élément de la liste chaînée
//         current = current->next;
//     }

//     // Attendre la fin de tous les processus enfants
//     for (int i = 0; i < index; i++) {
//         waitpid(pid_array[i], NULL, 0);
//     }

//     // Restaurer les descripteurs de fichier d'entrée et de sortie standard
//     dup2(saved_stdin, STDIN_FILENO);
//     dup2(saved_stdout, STDOUT_FILENO);
// }

// void check_line2(t_token **lst, char **env, t_minishell *exit_code) 
// {
//     int saved_stdin = dup(STDIN_FILENO);
//     int saved_stdout = dup(STDOUT_FILENO);
//     t_token *current = *lst;
//     int pid_array[1024]; 
//     int index = 0; 
    
//     while (current) 
//     {
//         // Sauvegarder les descripteurs de fichier d'entrée et de sortie standard
//         int fd_in = dup(STDIN_FILENO);
//         int fd_out = dup(STDOUT_FILENO);
        
//         // Gérer les redirections pour cette commande
//         int first_file = 0;
//         int last_file = 0;
//         first_file = manage_redirection_input(&current, exit_code, first_file);
//         last_file = manage_redirection_output(&current, last_file);
        
//         // Réinitialiser la position de lecture du fichier d'entrée
//         lseek(STDIN_FILENO, 0, SEEK_SET);
        
//         // Exécuter la commande avec un pipe s'il y a un pipe
//         if (current->type == CMD && (current->next != NULL && current->next->type == PIPE)) 
//         {
//             exec_cmd_with_pipe2(&current, exit_code, pid_array, index, env);
// 			// execute_commands_with_pipes(&current);
//             index++;
//         } 
//         // Sinon, exécuter une commande simple
//         else if (current->type == CMD) 
//         {
//             exec_simple_cmd(&current, exit_code, env);
//         }
//         // printf("Contenu de la liste chaînée après cette commande :\n");
//         // print_lst(current);
//         // Restaurer les descripteurs de fichier d'entrée et de sortie standard
//         dup2(fd_in, STDIN_FILENO);
//         dup2(fd_out, STDOUT_FILENO);
//         close(fd_in);
//         close(fd_out);
        
//         // Passer au prochain élément de la liste chaînée
//         current = current->next;
//     }

//     // Attendre la fin de tous les processus enfants
//     for (int i = 0; i < index; i++) {
//         waitpid(pid_array[i], NULL, 0);
//     }

//     // Restaurer les descripteurs de fichier d'entrée et de sortie standard
//     dup2(saved_stdin, STDIN_FILENO);
//     dup2(saved_stdout, STDOUT_FILENO);
// }

void check_line2(t_token **lst, char **env, t_minishell *exit_code) 
{
    t_token *current = *lst;
    int pid_array[1024]; 
    int index = 0; 

    while (current) 
    {
        if (current->type == CMD && current->next && current->next->type == PIPE)
        {
            int pipefd[2];
            if (pipe(pipefd) == -1) 
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }

            pid_t pid = fork();
            if (pid == -1) 
            {
                perror("fork");
                exit(EXIT_FAILURE);
            } 
            else if (pid == 0) // Processus enfant
            { 
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);

                exec_simple_cmd(&current, exit_code, env);
                exit(EXIT_SUCCESS);
            } 
            else // Processus parent
            {
                close(pipefd[1]);
                pid_array[index] = pid;
                index++;
            }
        }
        else if (current->type == CMD)
        {
            pid_t pid = fork();
            if (pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0) // Processus enfant
            {
                exec_simple_cmd(&current, exit_code, env);
                exit(EXIT_SUCCESS);
            }
            else // Processus parent
            {
                pid_array[index] = pid;
                index++;
            }
        }

        current = current->next;
    }

    // Attendre la fin de tous les processus enfants
    for (int i = 0; i < index; i++) {
        waitpid(pid_array[i], NULL, 0);
    }
}


void execute_commands_with_pipes_and_redirections(t_token **lst, char **env, t_minishell *exit_code) 
{
    t_token *current = *lst;
    int pid_array[1024]; 
    int index = 0; 

    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    while (current) 
    {
        // Gérer les redirections d'entrée
        int fd_in = -1;
        if (current->type == INPUT && current->next && current->next->type == CMD)
        {
            fd_in = open(current->content, O_RDONLY);
            if (fd_in == -1)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
            current = current->next; // Passer à la commande suivante
        }

        // Gérer les redirections de sortie
        int fd_out = -1;
        if ((current->type == OUTPUT || current->type == APPEND) && current->next && current->next->type == CMD)
        {
            if (current->type == OUTPUT)
                fd_out = open(current->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else // APPEND
                fd_out = open(current->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
            
            if (fd_out == -1)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
            current = current->next; // Passer à la commande suivante
        }

        if (current->type == CMD && current->next && current->next->type == PIPE)
        {
            int pipefd[2];
            if (pipe(pipefd) == -1) 
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }

            pid_t pid = fork();
            if (pid == -1) 
            {
                perror("fork");
                exit(EXIT_FAILURE);
            } 
            else if (pid == 0) // Processus enfant
            { 
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);

                exec_simple_cmd(&current, exit_code, env);
                exit(EXIT_SUCCESS);
            } 
            else // Processus parent
            {
                close(pipefd[1]);
                pid_array[index] = pid;
                index++;
            }
        }
        else if (current->type == CMD)
        {
            pid_t pid = fork();
            if (pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0) // Processus enfant
            {
                exec_simple_cmd(&current, exit_code, env);
                exit(EXIT_SUCCESS);
            }
            else // Processus parent
            {
                pid_array[index] = pid;
                index++;
            }
        }

        current = current->next;
    }

    // Attendre la fin de tous les processus enfants
    for (int i = 0; i < index; i++) {
        waitpid(pid_array[i], NULL, 0);
    }

    // Restaurer les descripteurs de fichier d'entrée et de sortie standard
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
}
