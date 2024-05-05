/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_new_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:13:49 by marvin            #+#    #+#             */
/*   Updated: 2024/05/04 22:13:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// int exec(..., ..., int *tab_pid)
// {
  
//   pid[n] = fork();
// }
// int tab_pid[1024]; // stocker de pid

// -> tu envoies le tableau a l'execution

// exec(..., ..., &tab_pid);
// for //element dans ton tab_pid
// waitpid(pid[i], NULL, 0);



void execute_pipeline(t_token **cmd_list, char **env, t_minishell *exit_code) {
    int pipefd[2];
    int prev_pipe_read = -1;
    t_token *current_cmd = *cmd_list;

    // Parcours de la liste des commandes
    while (current_cmd) 
    {
        // Création du pipe pour interconnecter les commandes
        if (pipe(pipefd) == -1) 
        {
            perror("Erreur lors de la création du pipe");
            exit(EXIT_FAILURE);
        }

        // Création d'un nouveau processus enfant
        pid_t pid = fork();
        if (pid == -1) {
            perror("Erreur lors de la création du processus enfant");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Processus enfant

            // Fermeture du descripteur de lecture du pipe en entrée
            close(pipefd[0]);

            // Redirection de l'entrée standard si ce n'est pas la première commande
            if (prev_pipe_read != -1) {
                dup2(prev_pipe_read, STDIN_FILENO);
                close(prev_pipe_read);
            }

            // Redirection de la sortie standard vers le descripteur d'écriture du pipe
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);

            // Exécution de la commande
            exec_cmd_with_fork(current_cmd->content, env, exit_code);
            exit(EXIT_FAILURE); // En cas d'échec de l'exécution de la commande
        } else {
            // Processus parent

            // Fermeture du descripteur d'écriture du pipe en sortie
            close(pipefd[1]);

            // Si ce n'est pas la première commande, fermeture du descripteur de lecture du pipe précédent
            if (prev_pipe_read != -1) {
                close(prev_pipe_read);
            }

            // Mise à jour du descripteur de lecture du pipe pour la prochaine commande
            prev_pipe_read = pipefd[0];

            // Passage à la prochaine commande dans la liste
            current_cmd = current_cmd->next;
        }
    }

    // Attente de la fin de tous les processus enfants
    while (wait(NULL) > 0 || (errno != ECHILD));
}
