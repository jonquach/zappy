/*
** get_team_name.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:36 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:36 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

int   get_team_name(t_args *option, char **av)
{
  int   i;

  i = 0;
  while (av[i] && av[i][0] != '-')
    i++;
  if ((option->team_name = malloc(sizeof(char *) * i + 1)) == NULL)
    printstr(2, "Error : malloc\n");
  i = 0;
  while (av[i] && av[i][0] != '-')
    {
      if ((option->team_name[i] = strdup(av[i])) == NULL)
        printstr(2, "Error : strdup\n");
      i++;
    }
  return (i);
}
