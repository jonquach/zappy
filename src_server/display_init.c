/*
** display_init.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:43 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:44 2015 Jonathan Quach
*/

#include <stdio.h>
#include "server.h"

void	display_init(t_args *option)
{
  int	i;

  i = 0;
  printf("--[WELCOME TO ZAPPY]--\n\n");
  printf("Listening on port %d...\n", option->port);
  printf("Configuration : \n- Max Player -> %d\n", option->nb_client);
  printf("- WorldX -> %d\n- WorldY -> %d\n", option->width, option->height);
  printf("Teams :\n");
  while (option->team_name[i] != NULL)
    {
      printf("Team %d : Name(%s) MaxPlayer(%d)\n",
	     i,
	     option->team_name[i],
	     option->nb_client);
      ++i;
    }
}
