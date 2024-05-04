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

/*
int exec(..., ..., int *tab_pid)
{
  
  pid[n] = fork();
}
int tab_pid[1024]; // stocker de pid

-> tu envoies le tableau a l'execution

exec(..., ..., &tab_pid);
for //element dans ton tab_pid
waitpid(pid[i], NULL, 0);
*\

// Fonction get_path pour obtenir le chemin de l'environnement
char *get_path(char **env) {
    while (ft_strncmp("PATH=", *env, 5) != 0 && *env && env)
        env++;
    return (*env + 5);
}

// Fonction check_path pour vérifier si le chemin d'accès est valide
char *check_path(char **paths, char *name) {
    char *join;
    char *tmp;
    int i = 0;
    while (paths[i]) {
        tmp = ft_strjoin(paths[i], "/");
        join = ft_strjoin(tmp, name);
        free(tmp);
        if (access(join, F_OK | X_OK) == 0)
            return (join);
        free(join);
        i++;
    }
    return (NULL);
}

// Fonction pour libérer la mémoire allouée pour un tableau de chaînes de caractères
void free_all(char **tab) {
    char **tmp = tab;
    while (*tab) {
        free(*tab);
        tab++;
    }
    free(tmp);
}

// Fonction pour exécuter une commande avec les paramètres spécifiés
void execute(char **param, char *path, char **env) {
    char **paths;
    char *path1;
    paths = ft_split(path, ':');
    path1 = check_path(paths, clean_quote(param[0]));
    if (!path1) {
        //free_all(paths);
        //free_all(param);
    }
    if (execve(path1, param, env) == -1) {
        //free_all(paths);
        //free_all(param);
    }
    //free_all(paths);
    //free_all(param);
    //free(path1);
}

int execute_builtin(ASTNode *node, char **env, char **param){
  printf("builtin : \n");
  if (ft_strcmp(clean_quote(param[0]), "cd") == 0)
    return (0);
  else if (ft_strcmp(clean_quote(param[0]), "pwd") == 0)
    printf("%s\n", get_cwd());
  else if (ft_strcmp(clean_quote(param[0]), "unset") == 0)
    return 0;
  else if (ft_strcmp(clean_quote(param[0]), "echo") == 0)
    echo(param);
  else if (ft_strcmp(clean_quote(param[0]), "export") == 0)
    exit(0);
  else if (ft_strcmp(clean_quote(param[0]), "env") == 0)
    print_env(env);
  else 
    return 1;
  print_env(env);
  exit(0);
}

// Fonction pour exécuter un nœud de l'arbre syntaxique abstrait (AST)
void exec(ASTNode* node, char **env, int test, int test2, int* pids, int* pid_count) {
    char **split_nodeValue;
    int p_id[2];
    pid_t pid;
    if (node == NULL || node->value == NULL) {
        return ;
    }
    if (pipe(p_id) == -1)
        exit(0);
    split_nodeValue = ft_split(node->value, ' ');
    if (ft_strcmp(clean_quote(split_nodeValue[0]), "exit") == 0)
        exit_program();
    else if (ft_strcmp(clean_quote(split_nodeValue[0]), "export") == 0)
        export_var(&env, split_nodeValue + 1);
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }
    if (pid == 0) {
        if (!(node->is_last_command)) {
            dup2(p_id[1], 1);
            close(p_id[0]);
        } else {
            dup2(test, 1);
            close(test);
        }
        if (is_builtin(clean_quote(split_nodeValue[0])))
          execute_builtin(node, env, split_nodeValue);
        execute(split_nodeValue, get_path(env), env);
    } else {
        if (!(node->is_last_command)) {
            close(p_id[1]);
            dup2(p_id[0], 0);
        } else {
            dup2(test2, STDIN_FILENO);
            close(test2);
        }
        pids[*pid_count] = pid;
        (*pid_count)++;
    }
}