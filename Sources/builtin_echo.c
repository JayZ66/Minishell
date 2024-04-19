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


void  echo(char *str)
{
  char    **cmd_with_options;
  size_t  i;

  i = 1;
  cmd_with_options = ft_split(str, ' ');
  if (cmd_with_options[1] && (ft_strcmp(cmd_with_options[1], "-n") != 0))
  {
    while (cmd_with_options[i])
    {
      printf("%s ", cmd_with_options[i]);
      if (cmd_with_options[i + 1] == NULL)
        printf("\n");
      i++;
    }
  }
  else if (ft_strcmp(cmd_with_options[1], "-n") == 0)
      handle_echo_with_n(cmd_with_options);
  else
    printf("\n");
}


/*
1. We need to check if -n
2. On le saut et on affiche tout le reste
3. On ne met pas de /n à la fin.
*/
void  handle_echo_with_n(char **cmd)
{
  size_t  i;

  i = 2;
  while (cmd[i])
  {
    if (cmd[i + 1] == NULL)
      printf("%s", cmd[i]);
    else
      printf("%s ", cmd[i]);
    i++;
  }
}

void  handle_quotes(char **cmd)
{
  size_t  i;
  size_t  j;
  char    *str;
  size_t  str_size;

  j = 0;
  str_size = 0;
  while(cmd[i])
  {
    i = 1;
    while (cmd[i][j])
    {
      if ((cmd[i][j] == '\'' || cmd[i][j] == '"') 
        && (cmd[i][ft_strlen(cmd[i]) - 1] == '\'' || cmd[i][ft_strlen(cmd[i]) - 1] == '"'))
        {
          if ((cmd[i][j + 1] == '\'' || cmd[i][j + 1] == '"') 
        && (cmd[i][ft_strlen(cmd[i]) - 2] == '\'' || cmd[i][ft_strlen(cmd[i]) - 2] == '"'))
          {
            j++;
            str_size = (ft_strlen(cmd[i] - 2) - j);
            str = ft_substr(cmd[i] + j, 0, str_size);
            cmd[i] = str;
          }
          else
          {
            str_size = (ft_strlen(cmd[i - 1]) - j);
            str = ft_substr(cmd[i] + j, 0, str_size);
            cmd[i] = str;
          }
        }
        j++;
    }
    i++;
  }
  // return (cmd);
}
/*
1. Si un simple/double quote ==> On retire
2. Si deux simple/double quote ==> On retire le premier niveau
*/


int main()
{
  char  *str;

  // str = "echo";
  // echo(str);
  // str = "echo -n cat cat cat";
  // echo(str);
  str = "echo cat cat cat";
  echo(str);
  
  return (0);
}