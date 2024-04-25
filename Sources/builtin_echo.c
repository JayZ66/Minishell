/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:33:23 by marvin            #+#    #+#             */
/*   Updated: 2024/04/16 20:33:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// void echo(char *str)
// {
//   char **tab;
//   char *new_str;
//   int j;
  
//   j = 0;
//   new_str = clean_quote(str);
//   tab = ft_split(new_str, ' ');
//   while (tab[j])
//   {
//     printf("%s ",tab[j]);
//     j++;
//   }
//   if (ft_strcmp(tab[1], "-n"))
//   {
//     printf("\n");
//   }
// }


void  builtin_echo(char *str)
{
  char    **cmd_with_options;
  char    *cleaned_quotes;
  size_t  i;

  i = 0;
  cleaned_quotes = handle_quotes(str);
  cmd_with_options = ft_split(cleaned_quotes, ' ');
  if (cmd_with_options[1] && (ft_strcmp(cmd_with_options[1], "-n") != 0) 
    && (ft_strcmp(cmd_with_options[0], "-n") != 0))
  {
    while (cmd_with_options[i])
    {
      if (ft_strcmp(cmd_with_options[i], "echo") == 0)
        i++;
      printf("%s ", cmd_with_options[i]);
      if (cmd_with_options[i + 1] == NULL)
        printf("\n");
      i++;
    }
  }
  else if (ft_strcmp(cmd_with_options[1], "-n") == 0 || ft_strcmp(cmd_with_options[0], "-n") == 0)
      handle_echo_with_n(cmd_with_options);
  else
    printf("\n");
  free_tab(cmd_with_options);
}


/*
1. We need to check if -n
2. On le saut et on affiche tout le reste
3. On ne met pas de /n à la fin.
*/
void  handle_echo_with_n(char **cmd)
{
  size_t  i;

  i = 1;
  while (cmd[i])
  {
    if (ft_strcmp(cmd[i], "-n") == 0)
      i++;
    if (cmd[i + 1] == NULL)
      printf("%s", cmd[i]);
    else
      printf("%s ", cmd[i]);
    i++;
  }
}

// char  *handle_quotes(char *cmd)
// {
//   size_t  i;
//   size_t  j;
//   size_t  z;
//   int     multiple_quotes;
//   int     first_quote;
//   char    *str;
//   size_t  str_size;

//   str_size = 0;
//   i = 0;
//   j = 0;
//   multiple_quotes = 0;
//   first_quote = 0;
//   while(cmd[i])
//   {
//     z = 0;
//     if (cmd[i] == '\'' || cmd[i] == '"') 
//     {
//       z = i + 1;
//       while (cmd[z] && cmd[z] != cmd[i])
//       {
//         if (cmd[z] == '\'' || cmd[z] == '"')
//           multiple_quotes = 1;
//          z++;
//        }
//      }
//      i++;
//   }
//   i = 0;
//   while (cmd[i])
//   {
//     if (multiple_quotes == 1)
//     {
//       if (first_quote != 1 && (cmd[i] == '\'' || cmd[i] == '"'))
//       {
//         first_quote = 1;
//         i++;
//       }
//       if (first_quote == 1 && (is_there_someting_after_quote(cmd + i) == 0))
//       {
//         str_size = ft_strlen(cmd + i) - 1;
//         str = ft_substr(cmd + i, 0, str_size);
//         return (str);
//       }
//       else if (first_quote == 1 && (is_there_someting_after_quote(cmd + i) == 1))
//       {
//         str = copy_str_without_first_quote(cmd);
//         return (str);
//       }
//     }
//     else if (cmd[i] == '\'' || cmd[i] == '"')
//     {
//       j = i + 1;
//       while (cmd[j])
//       {
//         if (cmd[j] == cmd[i] && (is_there_someting_after_quote(cmd + j) == 1))
//         {
//           str = copy_string_without_char(cmd, cmd[i]);
//           return (str);
//         }
//         j++;
//       }
//     }
//     else
//     {
//       if (cmd[i] == '\'' || cmd[i] == '"')
//       {
//         i++;
//         str_size = ft_strlen(cmd + i) - 1;
//         str = ft_substr(cmd + i, 0, str_size);
//         return (str);
//       }
//     }
//     i++;
//   }
//   return (cmd);
// }

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

char   *copy_str_without_first_quote(char *source)
{
    size_t  source_length;
    size_t  j;
    size_t  i;
    char    *result;
    
    source_length = strlen(source);
    j = 0;
    i = 0;
    if (source == NULL)
        return (NULL);
    result = (char *)malloc(source_length + 1); // Allouer suffisamment d'espace pour la chaîne copiée
    if (result == NULL)
        return (NULL);
    while (source[i] && i < source_length)
    {
      if (((source[i] == '\'' || source[i] == '"') && !(is_space(source[i - 1]))) && (!(is_space(source[i + 1])) && source[i + 1] != '\0' && i != 0))
      {
        result[j] = source[i];
        j++;
      }
      else if ((source[i] < 9 || source[i] > 13) && (source[i] != '\'' && source[i] != '"'))
      {
        result[j] = source[i];
        j++;
      }
      i++;
    }
    result[j] = '\0'; // Terminer la chaîne avec un caractère nul
    i = 0;
    return (result);
}

int is_there_something_after_quote(char *str)
{
  int i;
  int something_after;

  i = 0;
  something_after = 0;
  while (str[i])
  {
    if ((str[i] != ' ' && (str[i] < 9 || str[i] > 13))
      || ((str[i] == '\'' || str[i] == '"') && str[i + 1] == '\0'))
    {
      something_after = 1;
      return (something_after);
    }
    // else if ((str[i] == '\'' || str[i] == '"') 
    //     && (str[i + 1] == '\'' || str[i + 1] == '"'))
    //   return (something_after = 1, something_after);
    i++;
  }
  return (0);
}

char *copy_string_without_char(const char *source, char exclude_char)
{
    size_t  source_length;
    size_t  j;
    size_t  i;
    char    *result;
    
    source_length = strlen(source);
    j = 0;
    i = 0;
    if (source == NULL)
        return NULL;
    result = (char *)malloc(source_length + 1); // Allouer suffisamment d'espace pour la chaîne copiée
    if (result == NULL)
        return NULL;
    while (source[i] && i < source_length)
    {
      if (source[i] != exclude_char)
      {
        result[j] = source[i];
        j++;
      }
      i++;
    }
    result[j] = '\0'; // Terminer la chaîne avec un caractère nul
    return (result);
}

/*
1. Si un simple/double quote ==> On retire
2. Si deux simple/double quote ==> On retire le premier niveau
*/



