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


void execute_commands_with_pipes_and_redirections(t_clean_token **lst, char **env, t_minishell *exit_code) 
{
    t_clean_token *current = *lst;
    int pid_array[1024]; 
    int index = 0;
    int first_file;
    int last_file;

    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    while (current) 
    {
        last_file = 0;
        first_file = 0;
        first_file = manage_redirection_input(&current, exit_code, first_file);
        last_file = manage_redirection_output(&current, last_file);
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
                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[0]);
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
