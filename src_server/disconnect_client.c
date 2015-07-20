/*
** disconnect_client.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:17 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:18 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

void		disconnect(t_server *s, t_user *user)
{
  int		i;
  char		msg[BUFFER_SIZE];

  i = 0;
  memset(msg, 0, BUFFER_SIZE);
  sprintf(msg, "%d Player disconnected\n", user->fd);
  printstr(1, msg);
  create_ghost(s, user);
  while (s->team[i].name != NULL && user->team_name != NULL)
    {
      if (strcmp(s->team[i].name, user->team_name) == 0)
	{
	  if (s->team[i].nb < s->option->nb_client)
	    {
	      s->team[i].nb++;
	    }
	}
      ++i;
    }
  list_del_elem_at_position(&s->users, user->fd);
}
